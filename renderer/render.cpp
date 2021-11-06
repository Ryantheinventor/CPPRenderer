#include "render.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

namespace ryan 
{
	geometry makeGeometry(const vertex* verts, GLsizei vertCount, const GLuint* indices, GLsizei indexCount)
	{
		//create geo instance
		geometry newGeo = {};
		newGeo.size = indexCount;

		//generate buffers
		glGenVertexArrays(1, &newGeo.vao);
		glGenBuffers(1, &newGeo.vbo);
		glGenBuffers(1, &newGeo.ibo);

		//bind buffers
		glBindVertexArray(newGeo.vao);
		glBindBuffer(GL_ARRAY_BUFFER, newGeo.vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, newGeo.ibo);

		//buffer vertex data
		glBufferData(GL_ARRAY_BUFFER, vertCount * sizeof(vertex), verts, GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(GLsizei), indices, GL_STATIC_DRAW);

		//describe vertex data
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)16);

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)32);

		//unbind buffers
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		return newGeo;
	}

	void freeGeometry(geometry& geo)
	{
		glDeleteBuffers(1, &geo.vbo);
		glDeleteBuffers(1, &geo.ibo);
		glDeleteVertexArrays(1, &geo.vao);

		geo = {};
	}

	shader makeShader(const char* vertSource, const char* fragSource)
	{
		//make shader object
		shader newShad = {};
		newShad.program = glCreateProgram();

		//create shaders
		GLuint vert = glCreateShader(GL_VERTEX_SHADER);
		GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);

		//compile shaders
		glShaderSource(vert, 1, &vertSource, 0);
		glShaderSource(frag, 1, &fragSource, 0);
		glCompileShader(vert);
		glCompileShader(frag);

		//attach shaders
		glAttachShader(newShad.program, vert);
		glAttachShader(newShad.program, frag);

		//link shaders
		glLinkProgram(newShad.program);

		//delete shaders
		glDeleteShader(vert);
		glDeleteShader(frag);

		//return the shader object
		return newShad;
	}

	void freeShader(shader& shad)
	{
		glDeleteProgram(shad.program);
		shad = {};
	}

	texture loadTexture(const char* imagePath)
	{

		int imageWidth, imageHeight, imageFormat;
		unsigned char* rawPixelData = nullptr;

		stbi_set_flip_vertically_on_load(true);
		rawPixelData = stbi_load(imagePath, &imageWidth, &imageHeight, &imageFormat, STBI_default);

		texture tex = makeTexture(imageWidth, imageHeight, imageFormat, rawPixelData);
		stbi_image_free(rawPixelData);

		return tex;
	}

	texture makeTexture(unsigned width, unsigned height, unsigned channels, const unsigned char* pixels)
	{
		texture tex = { 0, width, height, channels };

		GLenum oglFormat = GL_RED;
		switch (channels) 
		{
		case 1:
			oglFormat = GL_RED;
			break;
		case 2:
			oglFormat = GL_RG;
			break;
		case 3:
			oglFormat = GL_RGB;
			break;
		case 4:
			oglFormat = GL_RGBA;
			break;
		}

		glGenTextures(1, &tex.handle);
		glBindTexture(GL_TEXTURE_2D, tex.handle);

		glTexImage2D(GL_TEXTURE_2D, 0, oglFormat, width, height, 0, oglFormat, GL_UNSIGNED_BYTE, pixels);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glBindTexture(GL_TEXTURE_2D, 0);

		return tex;
	}

	void freeTexture(texture& tex)
	{
		glDeleteTextures(1, &tex.handle);
		tex = {};
	}

	void draw(const shader& shad, const geometry& geo)
	{
		//bind the shader program
		glUseProgram(shad.program);
		//bind the VAO
		glBindVertexArray(geo.vao);

		//draw the object
		glDrawElements(GL_TRIANGLES, geo.size, GL_UNSIGNED_INT, nullptr);
	}

	void setUniform(const shader& shad, GLuint location, const mat4& value)
	{
		glProgramUniformMatrix4fv(shad.program, location, 1, GL_FALSE, &value[0][0]);
	}

	void setUniform(const shader& shad, GLuint location, const texture& value, int textureSlot)
	{
		glActiveTexture(GL_TEXTURE0 + textureSlot);
		glBindTexture(GL_TEXTURE_2D, value.handle);
		glProgramUniform1i(shad.program, location, textureSlot);
	}



}
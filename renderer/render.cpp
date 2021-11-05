#include "render.h"

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
}
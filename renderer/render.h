#pragma once

#include "glew/glew.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"



using namespace glm;

namespace ryan 
{
	struct vertex 
	{
		vec4 pos;
		vec4 color;
		vec2 uv;
		vec3 normals;
	};
	
	struct geometry
	{
		GLuint vao, vbo, ibo;
		GLuint size;
	};

	struct shader
	{
		GLuint program;
	};

	struct texture 
	{
		GLuint handle;
		unsigned width, height, channel;
	};

	geometry makeGeometry(const vertex* verts, GLsizei vertCount, const GLuint* indices, GLsizei indexCount);
	void freeGeometry(geometry& geo);

	shader makeShader(const char* vertSource, const char* fragSource);
	void freeShader(shader& shad);

	texture loadTexture(const char* imagePath);
	texture makeTexture(unsigned width, unsigned height, unsigned channels, const unsigned char* pixels);
	void freeTexture(texture& tex);

	void draw(const shader& shad, const geometry& geo);

	void setUniform(const shader& shad, GLuint location, const mat4& value);

	void setUniform(const shader& shad, GLuint location, const vec3& value);

	void setUniform(const shader& shad, GLuint location, const texture& value, int textureSlot);
}
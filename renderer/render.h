#pragma once

#include "glew/glew.h"
#include "glm/glm.hpp"
using namespace glm;

namespace ryan 
{
	struct vertex 
	{
		vec4 pos;
		vec4 color;
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

	geometry makeGeometry(const vertex* verts, GLsizei vertCount, const GLuint* indices, GLsizei indexCount);
	void freeGeometry(geometry& geo);

	shader makeShader(const char* vertSource, const char* fragSource);
	void freeShader(shader& shad);

	void draw(const shader& shad, const geometry& geo);
}
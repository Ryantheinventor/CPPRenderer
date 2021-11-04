#include "glm/glm.hpp"

#include <iostream>

#include "context.h"
#include "render.h"

using namespace ryan;

int main() 
{
	context window;
	window.init(640, 480, "Hello Window");

	//create triangle
	vertex triVerts[] =
	{
		{ { -.5f, -.5f, 0, 1} },
		{ { .5f, -.5f, 0, 1} },
		{ { 0, .5f, 0, 1} }
	};
	unsigned int triIndices[] = { 0, 1, 2 };
	geometry basicTriGeo = makeGeometry(triVerts, 3, triIndices, 3);

	//create shader
	const char * basicVert = 
		"#version 430 core\n"
		"layout (location = 0) in vec4 position;\n"
		"void main() { gl_Position = position; }";

	const char* basicFrag =
		"#version 430 core\n"
		"out vec4 vertColor;\n"
		"void main() { vertColor = vec4(1.0, 0.0, 0.0, 1.0); }";

	shader basicShad = makeShader(basicVert, basicFrag);

	//update-draw loop
	while (!window.shouldClose()) 
	{
		window.tick();
		
		//update
		

		//draw
		window.clear();

		draw(basicShad, basicTriGeo);

	}

	window.term();


	return 0;
}
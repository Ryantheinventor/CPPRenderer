#include "glm/glm.hpp"
#include <iostream>

#include "context.h"
#include "render.h"
#include "utils.h"
#include "glfw/glfw3.h"
#include "time.h"

using namespace ryan;

int main() 
{


	std::cout << glfwGetTime();


	context window;
	window.init(640, 480, "Hello Window");

	//create triangle
	vertex triVerts[] =
	{
		{ { -.5f, -.5f, 0, 1}, {1,0,0,1} },
		{ { -.2f, -.5f, 0, 1}, {0,1,0,1} },
		{ { -.35, -.2f, 0, 1}, {0,0,1,1} }
	};
	unsigned int triIndices[] = { 0, 1, 2 };
	geometry basicTriGeo = makeGeometry(triVerts, 3, triIndices, 3);

	//create rectangle
	vertex recVerts[] =
	{
		{ { -.5f, .2f, 0, 1}, {0,1,0,1} },
		{ { -.2f, .2f, 0, 1}, {1,0,0,1} },
		{ { -.2f, .5f, 0, 1}, {0,1,0,1} },
		{ { -.5f, .5f, 0, 1}, {0,0,1,1} }
	};
	unsigned int recIndices[] = { 0, 1, 2 , 0, 2, 3};
	geometry basicRecGeo = makeGeometry(recVerts, 4, recIndices, 6);

	shader basicShad = loadShader("res\\basic.vert", "res\\basic.frag");

	//update-draw loop
	while (!window.shouldClose()) 
	{
		window.tick();
		
		//update
		std::cout << window.gameTime.deltaTime() << "\n";
		//draw
		window.clear();

		draw(basicShad, basicTriGeo);

		draw(basicShad, basicRecGeo);

	}

	window.term();


	return 0;
}
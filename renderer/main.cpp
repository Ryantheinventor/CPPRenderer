#include "glm/glm.hpp"
#include <iostream>

#include "context.h"
#include "render.h"
#include "utils.h"
#include "glfw/glfw3.h"
#include "time.h"
#include "glm/ext.hpp"

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
		{ { .5f, -.5f, 0, 1}, {0,1,0,1} },
		{ { 0, .5f, 0, 1}, {0,0,1,1} }
	};
	unsigned int triIndices[] = { 0, 1, 2 , 2, 1, 0 };
	geometry basicTriGeo = makeGeometry(triVerts, 3, triIndices, 6);

	//create rectangle
	vertex recVerts[] =
	{
		{ { -.5f, -.5f, 0, 1}, {0,1,0,1} },
		{ { .5f, -.5f, 0, 1}, {0,0,1,1} },
		{ { .5f, .5f, 0, 1}, {0,1,0,1} },
		{ { -.5f, .5f, 0, 1}, {1,0,0,1} }
	};
	unsigned int recIndices[] = { 0, 1, 2 , 0, 2, 3 , 3, 2, 0, 2, 1, 0};
	geometry basicRecGeo = makeGeometry(recVerts, 4, recIndices, 12);

	shader basicShad = loadShader("res\\basic.vert", "res\\basic.frag");
	shader stdShad = loadShader("res\\mvp.vert", "res\\basic.frag");

	mat4 rec_model = identity<mat4>();
	mat4 tri_model = identity<mat4>();
	mat4 cam_view = lookAt(vec3(0, 1, 5),//pos
						   vec3(0, 0, 0),//look at
						   vec3(0, 1, 0));//up
	mat4 cam_proj = perspective(radians(60.f), //verticval fov
								640.f / 480.f, //aspect ratio
								0.1f, //new plane
								100.f); //far plane

	
	//update-draw loop
	while (!window.shouldClose()) 
	{
		window.tick();
		
		//update
		//std::cout << window.gameTime.deltaTime() << "\n";
		tri_model = rotate(tri_model, window.gameTime.deltaTime() * 10, vec3(0, 1, 0));
		rec_model = rotate(rec_model, window.gameTime.deltaTime() * 10, vec3(0, 1, 0));
		rec_model = translate(rec_model, vec3(0, sin(window.gameTime.programTime()) - vec3(rec_model[3]).y, 0));
		//tri_model = translate()
		//draw
		window.clear();

		setUniform(stdShad, 0, cam_proj);
		setUniform(stdShad, 1, cam_view);
		setUniform(stdShad, 2, tri_model);

		draw(stdShad, basicTriGeo);

		setUniform(stdShad, 2, rec_model);
		draw(stdShad, basicRecGeo);

	}

	window.term();


	return 0;
}
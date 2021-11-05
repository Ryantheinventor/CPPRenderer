#include "glm/glm.hpp"
#include <iostream>

#include "transofrm.h"
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
	unsigned int recIndices[] = { 0, 1, 2 , 0, 2, 3 , 3, 2, 0, 2, 1, 0 };
	geometry basicRecGeo = makeGeometry(recVerts, 4, recIndices, 12);

	//create cube
	vertex squareVerts[] =
	{
		{ { -.5f, -.5f, -.5f, 1}, {.5f,1,1,1} },
		{ { .5f, -.5f, -.5f, 1}, {1,.5f,1,1} },
		{ { -.5f, .5f, -.5f, 1}, {1,1,.5f,1} },
		{ { -.5f, -.5f, .5f, 1}, {.5f,.5f,1,1} },
		{ { .5f, .5f, -.5f, 1}, {1,.5f,.5f,1} },
		{ { -.5f, .5f, .5f, 1}, {.5f,1,.5f,1} },
		{ { .5f, -.5f, .5f, 1}, {.5f,.5f,.5f,1} },
		{ { .5f, .5f, .5f, 1}, {1,1,1,1} },
	};
	unsigned int squareIndices[] = { 0, 2, 1, 1, 2, 4, 1, 7, 6, 1, 4, 7, 3, 6, 5, 6, 7, 5, 3, 5, 0, 0, 5, 2, 0, 6, 3, 0, 1, 6, 2, 5, 7, 2, 7, 4 };
	geometry basicSquareGeo = makeGeometry(squareVerts, 8, squareIndices, 36);

	shader basicShad = loadShader("res\\basic.vert", "res\\basic.frag");
	shader stdShad = loadShader("res\\mvp.vert", "res\\basic.frag");
	
	mat4 cam_view = lookAt(vec3(0, 1, 5),//pos
						   vec3(0, 0, 0),//look at
						   vec3(0, 1, 0));//up
	mat4 cam_proj = perspective(radians(60.f), //verticval fov
								640.f / 480.f, //aspect ratio
								0.1f, //new plane
								100.f); //far plane

	transform triT = transform();
	transform recT = transform();

	triT.setParent(&recT);
	std::cout << recT.getChildCount();

	triT.localPos += vec3(0, 1.1, 0);
	recT.localPos = vec3(-2, 0, 0);
	recT.localRot = rotate(recT.localRot, 90 * 3.14f / 180.f, vec3(0, 0, 1));


	transform recT2 = transform();

	recT2.localPos += vec3(2, 0, 0);
	recT2.localScl = vec3(2, 2, 2);


	transform squareT = transform();
	transform squareTC = transform();
	squareTC.setParent(&squareT);

	squareT.localScl = vec3(.5f, .5f, .5f);

	squareTC.localPos = vec3(0, 1, 0);
	squareTC.localScl = vec3(.5f, .5f, .5f);


	//update-draw loop
	while (!window.shouldClose()) 
	{
		window.tick();
		
		//update
		//triT.localRot = rotate(triT.localRot, window.gameTime.deltaTime() * 10, vec3(0, 1, 0));

		recT.localRot = rotate(recT.localRot, window.gameTime.deltaTime() * 3, vec3(0, 1, 0));
		//recT.localScl = vec3(1.1 + sin(window.gameTime.programTime()), 1.1 + sin(window.gameTime.programTime()), 1);
		recT.localPos += vec3(0, sin(window.gameTime.programTime()) - recT.localPos.y, 0);

		recT2.localRot = rotate(recT2.localRot, window.gameTime.deltaTime() * 3, vec3(0, 1, 0));
		//recT2.localPos += vec3(0, sin(window.gameTime.programTime()) - recT2.localPos.y, 0);

		squareT.localRot = rotate(squareT.localRot, window.gameTime.deltaTime(), vec3(0, 1, 0));
		squareT.localRot = rotate(squareT.localRot, window.gameTime.deltaTime(), vec3(0, 0, 1));

		squareTC.localRot = rotate(squareT.localRot, window.gameTime.deltaTime(), vec3(0, 1, 0));
		squareTC.localRot = rotate(squareT.localRot, window.gameTime.deltaTime(), vec3(0, 0, 1));

		//tri_model = translate()
		//draw
		window.clear();

		setUniform(stdShad, 0, cam_proj);
		setUniform(stdShad, 1, cam_view);



		//setUniform(stdShad, 2, triT.worldMat());
		setUniform(stdShad, 2, recT.getChildAtIndex(0)->worldMat());
		draw(stdShad, basicTriGeo);
		
		setUniform(stdShad, 2, recT.worldMat());
		draw(stdShad, basicRecGeo);

		setUniform(stdShad, 2, recT2.worldMat());
		draw(stdShad, basicRecGeo);

		setUniform(stdShad, 2, squareT.worldMat());
		draw(stdShad, basicSquareGeo);

		setUniform(stdShad, 2, squareTC.worldMat());
		draw(stdShad, basicSquareGeo);

	}

	window.term();


	return 0;
}
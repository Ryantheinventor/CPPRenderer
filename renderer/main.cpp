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
	context window;
	window.init(640, 480, "Hello Window");

	//create triangle
	vertex triVerts[] =
	{
		{ { -.5f, -.5f, 0, 1}, {1,1,1,1}, {0,0}, {0,0,1}},
		{ { .5f, -.5f, 0, 1}, {1,1,1,1}, {1,0}, {0,0,1}},
		{ { 0, .5f, 0, 1}, {1,1,1,1}, {0.5f,1}, {0,0,1}},
		{ { -.5f, -.5f, 0, 1}, {1,1,1,1}, {0,0}, {0,0,-1}},
		{ { .5f, -.5f, 0, 1}, {1,1,1,1}, {1,0}, {0,0,-1}},
		{ { 0, .5f, 0, 1}, {1,1,1,1}, {0.5f,1}, {0,0,-1}}
	};
	unsigned int triIndices[] = { 0, 1, 2 , 5, 4, 3 };
	geometry basicTriGeo = makeGeometry(triVerts, 6, triIndices, 6);

	//create rectangle
	vertex recVerts[] =
	{
		{ { -.5f, -.5f, 0, 1}, {1,1,1,1}, {0,0}, {0,0,1}},
		{ { .5f, -.5f, 0, 1}, {1,1,1,1}, {1,0}, {0,0,1}},
		{ { .5f, .5f, 0, 1}, {1,1,1,1} , {1,1}, {0,0,1}},
		{ { -.5f, .5f, 0, 1}, {1,1,1,1}, {0,1}, {0,0,1}},
		{ { -.5f, -.5f, 0, 1}, {1,1,1,1}, {0,0}, {0,0,-1}},
		{ { .5f, -.5f, 0, 1}, {1,1,1,1}, {1,0}, {0,0,-1}},
		{ { .5f, .5f, 0, 1}, {1,1,1,1} , {1,1}, {0,0,-1}},
		{ { -.5f, .5f, 0, 1}, {1,1,1,1}, {0,1}, {0,0,-1}}
	};
	unsigned int recIndices[] = { 0, 1, 2 , 0, 2, 3 , 7, 6, 4, 6, 5, 4 };
	geometry basicRecGeo = makeGeometry(recVerts, 8, recIndices, 12);

	//create cube
	vertex cubeVerts[] =
	{
		{ { -.5f, -.5f, -.5f, 1}, {.5f,1,1,1}, {0,0}, {-1,0,0} },//0
		{ { -.5f, -.5f, .5f, 1}, {1,.5f,1,1}, {0,0}, {-1,0,0} },//1
		{ { -.5f, .5f, -.5f, 1}, {1,1,.5f,1}, {0,0}, {-1,0,0} },//2
		{ { -.5f, .5f, .5f, 1}, {.5f,.5f,1,1}, {0,0}, {-1,0,0} },//3
		{ { .5f, -.5f, -.5f, 1}, {1,.5f,.5f,1}, {0,0}, {0,0,-1} },//4
		{ { .5f, -.5f, .5f, 1}, {.5f,1,.5f,1}, {0,0}, {1,0,0} },//5
		{ { .5f, .5f, -.5f, 1}, {.5f,.5f,.5f,1}, {0,0}, {0,0,-1} },//6
		{ { .5f, .5f, .5f, 1}, {1,1,1,1}, {0,0}, {1,0,0} },//7

		{ { -.5f, -.5f, -.5f, 1}, {.5f,1,1,1}, {0,0}, {0,0,-1} },//8
		{ { -.5f, -.5f, .5f, 1}, {1,.5f,1,1}, {0,0}, {0,0,1} },//9
		{ { -.5f, .5f, -.5f, 1}, {1,1,.5f,1}, {0,0}, {0,0,-1} },//10
		{ { -.5f, .5f, .5f, 1}, {.5f,.5f,1,1}, {0,0}, {0,0,1} },//11
		{ { .5f, -.5f, -.5f, 1}, {1,.5f,.5f,1}, {0,0}, {1,0,0} },//12
		{ { .5f, -.5f, .5f, 1}, {.5f,1,.5f,1}, {0,0}, {0,0,1} },//13
		{ { .5f, .5f, -.5f, 1}, {.5f,.5f,.5f,1}, {0,0}, {1,0,0} },//14
		{ { .5f, .5f, .5f, 1}, {1,1,1,1}, {0,0}, {0,0,1} },//15

		{ { -.5f, -.5f, -.5f, 1}, {.5f,1,1,1}, {0,0}, {0,-1,0} },//16
		{ { -.5f, -.5f, .5f, 1}, {1,.5f,1,1}, {0,0}, {0,-1,0} },//17
		{ { -.5f, .5f, -.5f, 1}, {1,1,.5f,1}, {0,0}, {0,1,0} },//18
		{ { -.5f, .5f, .5f, 1}, {.5f,.5f,1,1}, {0,0}, {0,1,0} },//19
		{ { .5f, -.5f, -.5f, 1}, {1,.5f,.5f,1}, {0,0}, {0,-1,0} },//20
		{ { .5f, -.5f, .5f, 1}, {.5f,1,.5f,1}, {0,0}, {0,-1,0} },//21
		{ { .5f, .5f, -.5f, 1}, {.5f,.5f,.5f,1}, {0,0}, {0,1,0} },//22
		{ { .5f, .5f, .5f, 1}, {1,1,1,1}, {0,0}, {0,1,0} }//23
	};
	unsigned int squareIndices[] = 
	{ 
		0,1,2,
		3,2,1,

		8,10,6,
		8,6,4,

		12,14,7,
		12,7,5,

		13,15,11,
		13,11,9,

		18,19,23,
		18,23,22,

		17,16,20,
		17,20,21
	};
	geometry basicSquareGeo = makeGeometry(cubeVerts, 24, squareIndices, 36);

	texture colorTex = loadTexture("textures\\COLOR.png");
	texture whiteTex = loadTexture("textures\\WHITE.png");

	shader basicShad = loadShader("res\\basic.vert", "res\\basic.frag");
	//shader stdShad = loadShader("res\\mvp.vert", "res\\basic.frag");
	shader texShad = loadShader("res\\mvp.vert", "res\\mvp.frag");
	
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


	transform cubeT = transform();
	transform cubeTC = transform();
	cubeTC.setParent(&cubeT);

	cubeT.localScl = vec3(.5f, .5f, .5f);

	cubeTC.localPos = vec3(0, 1, 0);
	cubeTC.localScl = vec3(.5f, .5f, .5f);

	vec3 ambient(0.3f);
	vec3 directional(0, -0.707f, -0.707f);
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

		cubeT.localRot = rotate(cubeT.localRot, window.gameTime.deltaTime() * 5, vec3(0, 1, 0));
		cubeT.localRot = rotate(cubeT.localRot, window.gameTime.deltaTime() * 5, vec3(0, 0, 1));

		cubeTC.localRot = rotate(cubeT.localRot, window.gameTime.deltaTime() * 5, vec3(0, 1, 0));
		cubeTC.localRot = rotate(cubeT.localRot, window.gameTime.deltaTime() * 5, vec3(0, 0, 1));

		//tri_model = translate()
		//draw
		window.clear();

		/*setUniform(stdShad, 0, cam_proj);
		setUniform(stdShad, 1, cam_view);*/


		setUniform(texShad, 0, cam_proj);
		setUniform(texShad, 1, cam_view);

		setUniform(texShad, 3, colorTex, 0);
		setUniform(texShad, 4, ambient);
		setUniform(texShad, 5, directional);

		//setUniform(stdShad, 2, triT.worldMat());
		setUniform(texShad, 2, recT.getChildAtIndex(0)->worldMat());
		draw(texShad, basicTriGeo);
		
		setUniform(texShad, 2, recT.worldMat());
		draw(texShad, basicRecGeo);

		setUniform(texShad, 2, recT2.worldMat());
		draw(texShad, basicRecGeo);


		setUniform(texShad, 3, whiteTex, 0);

		setUniform(texShad, 2, cubeT.worldMat());
		draw(texShad, basicSquareGeo);

		setUniform(texShad, 2, cubeTC.worldMat());
		draw(texShad, basicSquareGeo);

	}

	window.term();


	return 0;
}
#include "context.h"

#include <iostream>

#include "glew/glew.h"
#include "glfw/glfw3.h"

namespace ryan 
{

	// Error callback called by OpenGL whenever a problem occurs (vendor-dependent)
	void APIENTRY errorCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
		GLsizei length, const GLchar* message,
		const void* userParam)
	{
		std::cerr << message << std::endl;
	}

	bool context::init(int width, int height, const char* title)
	{
		//init glfw
		glfwInit();

		//create window
		window = glfwCreateWindow(width, height, title, nullptr, nullptr);

		//set active
		glfwMakeContextCurrent(window);

		//init glew
		GLenum err = glewInit();
		if (GLEW_OK != err)
		{
			std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
			return false;
		}

		std::cout << "OpenGL Version: " << (const char*)glGetString(GL_VERSION) << "\n";
		std::cout << "Renderer: " << (const char*)glGetString(GL_RENDERER) << "\n";
		std::cout << "Vendor: " << (const char*)glGetString(GL_VENDOR) << "\n";
		std::cout << "GLSL: " << (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";

#if _DEBUG
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

		glDebugMessageCallback(errorCallback, 0);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, 0, true);
#endif

		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDepthFunc(GL_LEQUAL);
		glFrontFace(GL_CCW);
		glCullFace(GL_BACK);

		glClearColor(0.25f, 0.25f, 0.25f, 1);
		return true;
	}

	void context::tick()
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	void context::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void context::term()
	{
		//destroy window
		glfwDestroyWindow(window);

		//clean up
		glfwTerminate();
	}

	bool context::shouldClose() const
	{
		return glfwWindowShouldClose(window);
	}
}

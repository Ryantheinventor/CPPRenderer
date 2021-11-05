#pragma once

#include <iostream>

#include "glew/glew.h"
#include "glfw/glfw3.h"
#include "time.h"

namespace ryan
{
	class context
	{
		GLFWwindow* window;

	public:
		time gameTime;
		bool init(int width, int height, const char* title);
		void tick();
		void clear();
		void term();

		bool shouldClose() const;
	};
}
#pragma once
#include "glfw/glfw3.h"
namespace ryan 
{
	class time 
	{
	private:
		float totalTime; //time since start of program
		float lastDeltaTime; //time at the end of last frame
		float curDelta;
	public:
		float programTime() const; //time since start of program
		float deltaTime() const; //time between frames

		void updateTime(); //update stored values
		void resetTime(); //reset time to zero
		void setTime(float newTime); //set time to a new value
	};
}
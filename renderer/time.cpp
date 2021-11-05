#include "time.h"

namespace ryan
{
	float time::programTime() const
	{
		return totalTime;
	}
	float time::deltaTime() const
	{
		return curDelta;
	}
	void time::updateTime()
	{
		totalTime = glfwGetTime();
		curDelta = totalTime - lastDeltaTime;
		lastDeltaTime = totalTime;
	}

	void time::resetTime()
	{
		setTime(0);
	}

	void time::setTime(float newTime)
	{
		lastDeltaTime = newTime - curDelta;
		glfwSetTime(newTime);
	}

	

}
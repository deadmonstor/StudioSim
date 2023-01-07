#pragma once
#include "Library/glfw3.h"
#include "Util/Logger.h"
#include "Util/SingletonTemplate.h"
#include "Util/Events/EngineEvents.h"
#include "Util/Events/Events.h"

class KeyboardInput : public SingletonTemplate<KeyboardInput>
{
public:
	void keyCallback(GLFWwindow* window, const int key, const int scancode, const int action, int mods)
	{
		if (action == GLFW_PRESS)
		{
			Griddy::Events::invoke<OnKeyDown>(key, scancode);
		}
		else if (action == GLFW_RELEASE)
		{
			Griddy::Events::invoke<OnKeyUp>(key, scancode);
		}
		else if (action == GLFW_REPEAT)
		{
			Griddy::Events::invoke<OnKeyRepeat>(key, scancode);
		}
		
	}
};

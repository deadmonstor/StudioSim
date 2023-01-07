#pragma once
#include "Library/glfw3.h"
#include "Util/SingletonTemplate.h"
#include "Util/Events/EngineEvents.h"
#include "Util/Events/Events.h"

class Input : public SingletonTemplate<Input>
{
public:
	void keyCallback(GLFWwindow* window, const int key, const int scancode, const int action, int mods) const
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

	void mouseCallback(GLFWwindow* window, const int key, const int action, int mods) const
	{
		if (action == GLFW_PRESS)
		{
			Griddy::Events::invoke<OnMouseDown>(key, action);
		}
		else if (action == GLFW_RELEASE)
		{
			Griddy::Events::invoke<OnMouseUp>(key, action);
		}
	}
};

#pragma once
#include "Core/Renderer/Renderer.h"
#include "Library/glfw3.h"
#include "Util/SingletonTemplate.h"
#include "Util/Events/EngineEvents.h"
#include "Util/Events/Events.h"

static bool s_DebugKeyEvents = false;
static bool s_DebugMouseEvents = false;
class Input : public SingletonTemplate<Input>
{
public:
	void DebugEventChanged(const OnDebugEventChanged* event)
	{
		if (event->key == DebugKeyEvents)
			s_DebugKeyEvents = !s_DebugKeyEvents;

		if (event->key == DebugMouseEvents)
			s_DebugMouseEvents = !s_DebugMouseEvents;
	}
	
	void init()
	{
		Griddy::Events::subscribe(this, &Input::DebugEventChanged);
	}
	
	void keyCallback(GLFWwindow* window, const int key, const int scancode, const int action, int mods) const
	{
		if (action == GLFW_PRESS)
		{
			Griddy::Events::invoke<OnKeyDown>(key, scancode);

			if (s_DebugKeyEvents)
			{
				const std::string strs = getKeyName(key, scancode);
				LOG_INFO("Press: " + strs);
			}
		}
		else if (action == GLFW_RELEASE)
		{
			Griddy::Events::invoke<OnKeyUp>(key, scancode);
			
			if (s_DebugKeyEvents)
			{
				const std::string strs = getKeyName(key, scancode);
				LOG_INFO("Release: " + strs);
			}
		}
		else if (action == GLFW_REPEAT)
		{
			Griddy::Events::invoke<OnKeyRepeat>(key, scancode);
			
			if (s_DebugKeyEvents)
			{
				const std::string strs = getKeyName(key, scancode);
				LOG_INFO("Repeat: " + strs);
			}
		}
	}
	void mouseCallback(GLFWwindow* window, const int key, const int action, int mods) const
	{
		if (action == GLFW_PRESS)
		{
			Griddy::Events::invoke<OnMouseDown>(key, action);

			if (s_DebugMouseEvents)
			{
				const std::string strs(std::to_string(key));
				LOG_INFO("Mouse-Down: " + strs);

				const glm::vec2 mousePos = getMousePosition();
				LOG_INFO("Mouse Position: " + std::to_string(mousePos.x) + ", " + std::to_string(mousePos.y));
			}
		}
		else if (action == GLFW_RELEASE)
		{
			Griddy::Events::invoke<OnMouseUp>(key, action);

			if (s_DebugMouseEvents)
			{
				const std::string strs(std::to_string(key));
				LOG_INFO("Mouse-Down: " + strs);

				const glm::vec2 mousePos = getMousePosition();
				LOG_INFO("Mouse Position: " + std::to_string(mousePos.x) + ", " + std::to_string(mousePos.y));
			}
		}
	}

	void dropCallback(GLFWwindow* window, const int count, const char** paths) const
	{
		Griddy::Events::invoke<OnFileDropCallback>(count, paths);
	}

	static glm::vec2 getMousePosition()
	{
		double x, y;
		glfwGetCursorPos(glfwGetCurrentContext(), &x, &y);
		
		const glm::vec2 windowSize = Renderer::GetWindowSize();
		x = std::clamp(x, 0.0, static_cast<double>(windowSize.x));
		y = std::clamp(y, 0.0, static_cast<double>(windowSize.y));
		return {x, y};
	}

	static std::string getKeyName(const int key, const int scancode)
	{
		const char* str = glfwGetKeyName(key, scancode);
		if (!str) return "";
		return str;
	}
};

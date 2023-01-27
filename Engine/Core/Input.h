#pragma once
#include "Pivot.h"
#include "Core/GameObject.h"
#include "Core/Components/Transform.h"
#include "Core/Renderer/Renderer.h"
#include "glm/ext/matrix_projection.hpp"
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

				glm::vec2 mousePos = getMousePosition();
				LOG_INFO("Mouse Position: " + std::to_string(mousePos.x) + ", " + std::to_string(mousePos.y));
				
				mousePos = getMousePositionScreenSpace();
				LOG_INFO("Mouse Position Screen Space: " + std::to_string(mousePos.x) + ", " + std::to_string(mousePos.y));
			}
		}
		else if (action == GLFW_RELEASE)
		{
			Griddy::Events::invoke<OnMouseUp>(key, action);

			if (s_DebugMouseEvents)
			{
				const std::string strs(std::to_string(key));
				LOG_INFO("Mouse-Up: " + strs);

				glm::vec2 mousePos = getMousePosition();
				LOG_INFO("Mouse Position: " + std::to_string(mousePos.x) + ", " + std::to_string(mousePos.y));
				
				mousePos = getMousePositionScreenSpace();
				LOG_INFO("Mouse Position Screen Space: " + std::to_string(mousePos.x) + ", " + std::to_string(mousePos.y));
			}
		}
	}

	void dropCallback(GLFWwindow* window, const int count, const char** paths) const
	{
		Griddy::Events::invoke<OnFileDropCallback>(count, paths);
	}

	static glm::vec2 getMousePosition()
	{
		if (SceneManager::Instance()->isShuttingDown())
			return glm::vec2(0.0f);
		
		double x, y;
		glfwGetCursorPos(glfwGetCurrentContext(), &x, &y);
		glm::vec2 test = getMousePositionScreenSpace();

		test.y = Renderer::Instance()->getWindowSize().y - test.y;

		// TODO: Fix this to work with any resolution and aspect ratio (currently only works with 16:9) 
		x = (1120 * (test.x / Renderer::Instance()->getWindowSize().x)) - 560;
		y = (580 * (test.y / Renderer::Instance()->getWindowSize().y)) - 290;

		x += Renderer::Instance()->getCameraPos().x;
		y += Renderer::Instance()->getCameraPos().y;
		
		return {x, y};
	}

	static glm::vec2 getMousePositionScreenSpace()
	{
		if (SceneManager::Instance()->isShuttingDown())
			return glm::vec2(0.0f);
		
		double x, y;
		int topLeftX, topLeftY;
		glfwGetCursorPos(glfwGetCurrentContext(), &x, &y);
		glfwGetWindowPos(glfwGetCurrentContext(), &topLeftX, &topLeftY);

		float absoluteCursorX = topLeftX + static_cast<int>(std::floor(x));
		float absoluteCursorY = topLeftY + static_cast<int>(std::floor(y));

		glm::vec2 pos = { absoluteCursorX, absoluteCursorY };
		
		return {pos.x, pos.y};
	}


	static std::string getKeyName(const int key, const int scancode)
	{
		const char* str = glfwGetKeyName(key, scancode);
		if (!str) return "";
		return str;
	}
};

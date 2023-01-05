﻿#include "Engine.h"
#include <Windows.h>
#include "Library/glfw3.h"
#include "Util/Events/Events.h"
#include "Util/ImGuiHandler.h"
#include "Util/Logger.h"
#include "Util/Time.h"
#include "WindowManager.h"
#include "KeyboardInput.h"

namespace Disunity
{
	void key_callback(GLFWwindow* window, const int key, const int scancode, const int action, const int mods)
	{
		KeyboardInput::Instance()->keyCallback(window, key, scancode, action, mods);
	}

	bool Engine::init()
	{
		if (!internalInit())
		{
			LOG_ERROR("Engine failed to initialize");

			// TODO: Should cleanup actually be here?
			cleanup();
			return false;
		}

		LOG_INFO("Engine initialized");
		return true;
	}

	bool Engine::internalInit()
	{
		// Do not move this logging down it will crash
		Logger::Instance()->init();
		if (!WindowManager::Instance()->createWindow(""))
		{
			return false;
		}

#if (!NDEBUG)
		ImGuiHandler::Instance()->init();
#endif
		m_Initialized = true;

		glfwSetKeyCallback(WindowManager::Instance()->GetWindow(), key_callback);

		// init
		return true;
	}

	void Engine::update()
	{
		// update
		glfwPollEvents();

#if (!NDEBUG)
		ImGuiHandler::Instance()->update();
#endif
		
		// Check if we need to stop the engine
		if (auto *window = WindowManager::Instance()->GetWindow(); window == nullptr || glfwWindowShouldClose(window))
		{
			m_Running = false;
		}
	}

	void Engine::render()
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

#if (!NDEBUG)
		ImGuiHandler::Instance()->render();
#endif

		// render
		glfwSwapBuffers(WindowManager::Instance()->GetWindow());
	}

	void Engine::cleanup()
	{
		WindowManager::Instance()->cleanup();
#if (!NDEBUG)
		ImGuiHandler::Instance()->cleanup();
#endif
		glfwTerminate();
	}

	void Engine::run()
	{
		if (!m_Initialized)
		{
			LOG_ERROR("Engine not initialized");
			return;
		}

		Time::update();
		m_Running = true;

		while (m_Running)
		{
			Time::update();

			update();
			render();
		}

		cleanup();
	}
}
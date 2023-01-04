#include "Engine.h"
#include <Windows.h>
#include "Library/glfw3.h"
#include "Util/Events/Events.h"
#include "Util/Logger.h"
#include "Util/Time.h"
#include "WindowManager.h"

namespace Disunity
{
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

		m_Initialized = true;
		
		// init
		return true;
	}

	void Engine::update()
	{
		// update
		glfwPollEvents();

		// Check if we need to stop the engine
		if (auto *window = WindowManager::Instance()->GetWindow();
				window == nullptr || glfwWindowShouldClose(window))
		{
			m_Running = false;
		}
	}

	void Engine::render()
	{
		// render
		glfwSwapBuffers(WindowManager::Instance()->GetWindow());
	}

	void Engine::cleanup()
	{
		WindowManager::Instance()->cleanup();
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
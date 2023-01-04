#include "Engine.h"

#include "Library/glfw3.h"
#include "Util/Events/Events.h"
#include "Util/Logger.h"
#include "Util/Time.h"
#include "WindowManager.h"

namespace Disunity
{
	bool Engine::init()
	{
		// Do not move this logging down it will crash
		Logger::Instance()->init();

		const int sub_index = Events::Instance()->subscribe(this, &Engine::onEvent); // Subscribes to the event system
		Events::Instance()->invoke(new Event()); // Will call onEvent
		Events::Instance()->invoke(new Event()); // Will call onEvent
		Events::Instance()->unsubscribe(this, &Engine::onEvent, sub_index); // Unsubscribes from the event system
		Events::Instance()->invoke(new Event()); // Will not call onEvent

		if (!WindowManager::Instance()->CreateWindow_Diff())
		{
			return false;
		}
		// init
		return true;
	}

	void Engine::onEvent(Event* test)
	{
		// on event
		LOG_INFO("Event");
	}

	void Engine::update()
	{
		// update
		glfwPollEvents();    
	}

	void Engine::render()
	{
		// render
		glfwSwapBuffers(WindowManager::Instance()->GetWindow());
	}

	void Engine::cleanup()
	{
		// cleanup
	}

	void Engine::run()
	{
		if (!init())
		{
			LOG_ERROR("Engine failed to initialize");

			// TODO: Should cleanup actually be here?
			cleanup();
			return;
		}

		LOG_INFO("Engine initialized");

		Time::update();

		m_Initialized = true;
		m_Running = true;

		while (m_Running)
		{
			Time::update();
			
			update();
			render();

			if (glfwWindowShouldClose(WindowManager::Instance()->GetWindow()))
			{
				m_Running = false;
			}
		}

		cleanup();
	}
}
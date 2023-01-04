#include "Engine.h"
#include "Util/Events/Events.h"
#include "Util/Logger.h"

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
	}

	void Engine::render()
	{
		// render
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

		m_Initialized = true;
		m_Running = true;

		while (m_Running)
		{
			update();
			render();
		}

		cleanup();
	}
}
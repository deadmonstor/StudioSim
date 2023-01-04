#include "Engine.h"
#include "Util/Logger.h"

namespace Disunity
{
	bool Engine::init()
	{
		// Do not move this logging down it will crash
		Logger::GetInstance()->Init();

		// init

		return true;
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
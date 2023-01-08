#pragma once
#include "Util/SingletonTemplate.h"

namespace Griddy
{
	class Event;
	class Engine : public SingletonTemplate<Engine>
	{
	public:
		bool init();
		void run();
		void shutdown();

		static bool isRunning() { return Instance()->m_Running; }
		static bool isInitialized() { return Instance()->m_Initialized; }
	private:
		bool m_Running = false;
		bool m_Initialized = false;

		bool internalInit();
		void update();
		void lateUpdate();
		void render();
		void cleanup();
	};
}
#pragma once
#include "Util/SingletonTemplate.h"

namespace Disunity
{
	class Event;
	class Engine : public SingletonTemplate<Engine>
	{
	public:
		void run();

		static bool isRunning() { return Instance()->m_Running; }
		static bool isInitialized() { return Instance()->m_Initialized; }
	private:
		bool m_Running = false;
		bool m_Initialized = false;

		bool init();
		void update();
		void onEvent(Event* event);
		void render();
		void cleanup();
	};
}
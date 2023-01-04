#pragma once
#include <string>


#include "Util/SingletonTemplate.h"

namespace Disunity
{
	class Event;
	class Engine : public SingletonTemplate<Engine>
	{
	public:
		bool init();
		void run();

		static bool isRunning() { return Instance()->m_Running; }
		static bool isInitialized() { return Instance()->m_Initialized; }
	private:
		bool m_Running = false;
		bool m_Initialized = false;

		bool internalInit();
		void update();
		void render();
		void cleanup();
	};
}
#pragma once
#include "Util/SingletonTemplate.h"

namespace Disunity
{
	class Engine : public SingletonTemplate<Engine>
	{
	public:
		void run();
		
		static bool isRunning() { return GetInstance()->m_Running; }
		static bool isInitialized() { return GetInstance()->m_Initialized; }
	private:
		bool m_Running = false;
		bool m_Initialized = false;
		
		bool init();
		void update();
		void render();
		void cleanup();
	};
}
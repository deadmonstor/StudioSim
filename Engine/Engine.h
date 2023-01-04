#pragma once
#include "Util/SingletonTemplate.h"

namespace Disunity
{
	class Engine : public SingletonTemplate<Engine>
	{
		bool m_Running = false;
		bool m_Initialized = false;

		void m_SetupLogger();
		bool m_Init();
		void m_Update();
		void m_Render();
		void m_Cleanup();

	public:
		void Run();
		
		static bool IsRunning() { return GetInstance()->m_Running; }
		static bool IsInitialized() { return GetInstance()->m_Initialized; }
	};
}
#pragma once
#include "Util/SingletonTemplate.h"
#include "Util/Events/EngineEvents.h"

namespace Griddy
{
	class Event;
	class Engine : public SingletonTemplate<Engine>
	{
	public:
		bool init();
		void run();
		void shutdown();
		void onDebugEvent(const OnDebugEventChanged* event);

		static bool isRunning() { return Instance()->m_Running; }
		static bool isPaused() { return Instance()->m_Paused; }
		static bool isInitialized() { return Instance()->m_Initialized; }

		static void setPaused(const bool paused) { Instance()->m_Paused = paused; }
	private:
		bool m_Running = false;
		bool m_Paused = false;
		bool m_Initialized = false;

		bool internalInit();
		void update();
		void lateUpdate();
		void render();
		void cleanup();
	};
}

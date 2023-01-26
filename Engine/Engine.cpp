#include "Engine.h"
#include <Windows.h>
#include "Core/Components/TextRenderer.h"
#include "Core/Input.h"
#include "Core/AudioEngine.h"
#include "Core/SceneManager.h"
#include "Core/Grid/GridSystem.h"
#include "Core/Renderer/Lighting.h"
#include "Core/Renderer/Renderer.h"
#include "Core/Renderer/ResourceManager.h"
#include "imgui/imgui_impl_glfw.h"
#include "Util/ImGuiHandler.h"
#include "Util/Logger.h"
#include "Util/Time.h"
#include "Util/Events/EngineEvents.h"
#include "Util/Events/Events.h"
#include "UIManager.h"


namespace Griddy
{
	void key_callback(GLFWwindow* window, const int key, const int scancode, const int action, const int mods)
	{
#if (!NDEBUG)
		ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
#endif

		if (!Engine::isPaused())
			Input::Instance()->keyCallback(window, key, scancode, action, mods);
		
		ImGuiHandler::Instance()->onKeyDown(key, scancode, action, mods);
	}

	void mouse_callback(GLFWwindow* window, const int button, const int action, const int mods)
	{
#if (!NDEBUG)
		ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);
		
		if (!ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow))
		{
#endif
			if (!Engine::isPaused())
				Input::Instance()->mouseCallback(window, button, action, mods);

#if (!NDEBUG)
		}
#endif
	}

	void drop_callback(GLFWwindow* window, const int count, const char** paths)
	{
		if (!Engine::isPaused())
			Input::Instance()->dropCallback(window, count, paths);
	}
	
	bool Engine::init()
	{
		if (!internalInit())
		{
			LOG_ERROR("Engine failed to initialize");

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

		if (!Renderer::Instance()->createWindow(""))
		{
			return false;
		}

		Lighting::Instance()->init();
		AudioEngine::Instance()->init();
		Input::Instance()->init();
		TextRenderer::Instance()->init();
		m_Initialized = true;
		ImGuiHandler::Instance()->init();

		glfwSetKeyCallback(Renderer::getWindow(), key_callback);
		glfwSetMouseButtonCallback(Renderer::getWindow(), mouse_callback);
		glfwSetDropCallback(Renderer::getWindow(), drop_callback);

		Events::subscribe(this, &Engine::onDebugEvent);
		// init
		return true;
	}

	void Engine::update()
	{
		// update
		glfwPollEvents();

		if (!isPaused())
		{
			SceneManager::Instance()->update();
			Events::invoke<OnEngineUpdate>();
			
			AudioEngine::Instance()->update();
		}
		// Check if we need to stop the engine
		if (auto *window = Renderer::getWindow(); window == nullptr || glfwWindowShouldClose(window))
		{
			m_Running = false;
		}
		
		ImGuiHandler::Instance()->update();
	}


	void Engine::render()
	{
		glClearColor(0, 0, 0, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		GridSystem::Instance()->render();

		Renderer::Instance()->render();
		SceneManager::Instance()->render();
		UIManager::Instance()->render();

		Events::invoke<OnEngineRender>();
		
		ImGuiHandler::render();
		glfwSwapBuffers(Renderer::getWindow());
	}

	void Engine::lateUpdate()
	{
		SceneManager::Instance()->lateUpdate();
		
		Events::unsubscribeQueueFunc();
	}
	
	void Engine::cleanup()
	{
		Renderer::Instance()->cleanup();
		ImGuiHandler::cleanup();

		Events::invoke<OnEngineStop>();
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

		Renderer::Instance()->init();
		ResourceManager::LoadTexture("Sprites\\image.png", "face");
		ResourceManager::LoadTexture("Sprites\\rock_n.png", "normals");
		ResourceManager::LoadTexture("Sprites\\image2.png", "face2");
		ResourceManager::LoadTexture("Sprites\\engine.png", "engine");

		if (!SceneManager::Instance()->init())
		{
			LOG_ERROR("Failed to load default scene");
			return;
		}
		
		bool firstFrame = true;
		
		while (m_Running)
		{
			Time::update();

			update();
			render();
			lateUpdate();

			if (firstFrame)
			{
				Events::invoke<OnEngineStart>();
				firstFrame = false;
			}
		}

		cleanup();
	}

	void Engine::shutdown()
	{
		m_Running = false;
	}

	void Engine::onDebugEvent(const OnDebugEventChanged* event)
	{
		if (event->key == DebugPauseGame)
			setPaused(!isPaused());
	}
}

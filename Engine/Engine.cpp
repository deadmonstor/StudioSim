#include "Engine.h"
#include <Windows.h>
#include "AudioEngine.h"
#include "Input.h"
#include "Core/SceneManager.h"
#include "Core/Grid/GridSystem.h"
#include "Core/Renderer/Renderer.h"
#include "Core/Renderer/ResourceManager.h"
#include "imgui/imgui_impl_glfw.h"
#include "Util/ImGuiHandler.h"
#include "Util/Logger.h"
#include "Util/Time.h"
#include "Util/Events/EngineEvents.h"
#include "Util/Events/Events.h"

namespace Griddy
{
	void key_callback(GLFWwindow* window, const int key, const int scancode, const int action, const int mods)
	{
		ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
		Input::Instance()->keyCallback(window, key, scancode, action, mods);
	}

	void mouse_callback(GLFWwindow* window, const int button, const int action, const int mods)
	{
		ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);
		
		if (!ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow))
			Input::Instance()->mouseCallback(window, button, action, mods);
	}

	void drop_callback(GLFWwindow* window, int count, const char** paths)
	{
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
		
		AudioEngine::Instance()->init();
		Input::Instance()->init();
		ImGuiHandler::Instance()->init();
		m_Initialized = true;

		glfwSetKeyCallback(Renderer::GetWindow(), key_callback);
		glfwSetMouseButtonCallback(Renderer::GetWindow(), mouse_callback);
		glfwSetDropCallback(Renderer::GetWindow(), drop_callback);

		// init
		return true;
	}

	void Engine::update()
	{
		// update
		glfwPollEvents();

		SceneManager::Instance()->update();
		Events::invoke<OnEngineUpdate>();
		
		AudioEngine::Instance()->update();
		// Check if we need to stop the engine
		if (auto *window = Renderer::GetWindow(); window == nullptr || glfwWindowShouldClose(window))
		{
			m_Running = false;
		}
		
		ImGuiHandler::Instance()->update();
	}

	void Engine::lateUpdate()
	{
		SceneManager::Instance()->lateUpdate();
	}

	void Engine::render()
	{
		Renderer::Instance()->render();

		SceneManager::Instance()->render();
		GridSystem::Instance()->render();
		
		ImGuiHandler::render();
		glfwSwapBuffers(Renderer::GetWindow());
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

		if (!SceneManager::Instance()->init())
		{
			LOG_ERROR("Failed to load default scene");
			return;
		}
		
		ResourceManager::LoadTexture("shaders\\image.png", "face");
		ResourceManager::LoadTexture("shaders\\image2.png", "face2");
		ResourceManager::LoadTexture("shaders\\engine.png", "engine");
		
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
}

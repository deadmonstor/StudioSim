﻿#include "Engine.h"
#include <Windows.h>
#include "KeyboardInput.h"
#include "Core/SceneManager.h"
#include "Core/Grid/GridSystem.h"
#include "Core/Renderer/Renderer.h"
#include "Core/Renderer/ResourceManager.h"
#include "Util/ImGuiHandler.h"
#include "Util/Logger.h"
#include "Util/Time.h"
#include "Util/Events/EngineEvents.h"
#include "Util/Events/Events.h"
#include "AudioEngine.h"

namespace Griddy
{
	void key_callback(GLFWwindow* window, const int key, const int scancode, const int action, const int mods)
	{
		KeyboardInput::Instance()->keyCallback(window, key, scancode, action, mods);
	}

	bool Engine::init()
	{
		if (!internalInit())
		{
			LOG_ERROR("Engine failed to initialize");

			// TODO: Should cleanup actually be here?
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
		
		ImGuiHandler::Instance()->init();
		m_Initialized = true;

		AudioEngine::Instance()->init();
		glfwSetKeyCallback(Renderer::GetWindow(), key_callback);

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
		
		ResourceManager::LoadTexture("shaders\\image.png", false, "face");
		ResourceManager::LoadTexture("shaders\\image2.png", true, "face2");
		ResourceManager::LoadTexture("shaders\\engine.png", true, "engine");
		
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

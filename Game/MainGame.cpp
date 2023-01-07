﻿#include "MainGame.h"
#include <Util/Logger.h>
#include "TestGameplaySystem.h"
#include "Core/Renderer/Renderer.h"
#include "Util/Events/Events.h"

int main(int, char**)
{
	if (!MainGame::Instance()->init())
	{
		LOG_ERROR("Failed to initialize the game");
		return -1;
	}

	const auto Renderer = Renderer::Instance();
	Renderer->SetWindowTitle("Game Name Here");
	Renderer->SetWindowSize({ 1920, 1080 });

	ResourceManager::LoadTextureArray("shaders\\Blue-Slime-Idle\\", true, "Blue-Slime-Idle", 7);
	ResourceManager::LoadTextureArray("shaders\\Blue-Slime-Hurt\\", true, "Blue-Slime-Hurt", 11);
	ResourceManager::LoadTextureArray("shaders\\Fireball\\", true, "Fireball", 15);
	
	Griddy::Events::subscribe(TestGameplaySystem::Instance(), &TestGameplaySystem::TestFuncLewis);
	Griddy::Events::subscribe(TestGameplaySystem::Instance(), &TestGameplaySystem::TestFuncUpdate);

	Griddy::Events::subscribe(TestGameplaySystem::Instance(), &TestGameplaySystem::TestKeyDown);
	Griddy::Events::subscribe(TestGameplaySystem::Instance(), &TestGameplaySystem::TestKeyUp);
	Griddy::Events::subscribe(TestGameplaySystem::Instance(), &TestGameplaySystem::TestKeyRepeat);

	Griddy::Events::subscribe(TestGameplaySystem::Instance(), &TestGameplaySystem::TestMouseUp);
	Griddy::Events::subscribe(TestGameplaySystem::Instance(), &TestGameplaySystem::TestMouseDown);
	
	MainGame::Instance()->run();
	return 0;
}
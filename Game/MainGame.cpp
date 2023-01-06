#include "MainGame.h"
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

	const auto Events = Disunity::Events::Instance();
	Events->subscribe(TestGameplaySystem::Instance(), &TestGameplaySystem::TestFunc);
	Events->subscribe(TestGameplaySystem::Instance(), &TestGameplaySystem::TestFuncUpdate);
	Events->subscribe(TestGameplaySystem::Instance(), &TestGameplaySystem::TestKeyDown);
	Events->subscribe(TestGameplaySystem::Instance(), &TestGameplaySystem::TestKeyUp);
	Events->subscribe(TestGameplaySystem::Instance(), &TestGameplaySystem::TestKeyRepeat);
	
	MainGame::Instance()->run();
	return 0;
}
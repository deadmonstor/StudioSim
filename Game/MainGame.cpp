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
	Renderer->setWindowTitle("Game Name Here");
	Renderer->setWindowSize({ 1920, 1080 });

	ResourceManager::LoadTextureArray("Sprites\\Blue-Slime-Idle\\", "Blue-Slime-Idle", 7);
	ResourceManager::LoadTextureArray("Sprites\\Blue-Slime-Hurt\\", "Blue-Slime-Hurt", 11);
	ResourceManager::LoadTextureArray("Sprites\\Blue-Slime-Death\\", "Blue-Slime-Death", 14);
	ResourceManager::LoadTextureArray("Sprites\\Zombie\\", "Zombie", 8);
	ResourceManager::LoadTextureArray("Sprites\\Skeleton\\", "Skeleton", 8);
	ResourceManager::LoadTextureArray("Sprites\\Fireball\\", "Fireball", 15);
	ResourceManager::LoadTextureArray("Sprites\\FX1\\", "FXSCircle", 5);
	ResourceManager::LoadTextureArray("Sprites\\FX2\\", "FXSDrop", 8);
	ResourceManager::LoadTextureArray("Sprites\\FX3\\", "FXSExpl", 5);
	ResourceManager::LoadTextureArray("Sprites\\Red-Slash-Wide\\", "Red-Slash-Wide", 6);
	ResourceManager::LoadTextureArray("Sprites\\Red-Slash-Thin\\", "RedSlashThin", 6);
	ResourceManager::LoadTextureArray("Sprites\\player\\", "hero", 5);
	ResourceManager::LoadTexture("Sprites\\rock.png", "rock");
	ResourceManager::LoadTexture("Sprites\\background.png", "background");
	ResourceManager::LoadTexture("Sprites\\UE.png", "troll");
	
	Griddy::Events::subscribe(TestGameplaySystem::Instance(), &TestGameplaySystem::TestFunc);
	Griddy::Events::subscribe(TestGameplaySystem::Instance(), &TestGameplaySystem::TestFuncLewis);
	Griddy::Events::subscribe(TestGameplaySystem::Instance(), &TestGameplaySystem::TestInventory);
	Griddy::Events::subscribe(TestGameplaySystem::Instance(), &TestGameplaySystem::TestFuncUpdate);
	Griddy::Events::subscribe(TestGameplaySystem::Instance(), &TestGameplaySystem::testDropCallback);
	Griddy::Events::subscribe(TestGameplaySystem::Instance(), &TestGameplaySystem::testKeyDown);
	Griddy::Events::subscribe(TestGameplaySystem::Instance(), &TestGameplaySystem::testKeyUp);
	Griddy::Events::subscribe(TestGameplaySystem::Instance(), &TestGameplaySystem::testGameObjectDestroy);
	Griddy::Events::subscribe(TestGameplaySystem::Instance(), &TestGameplaySystem::testRender);
	
	Griddy::Events::subscribe(TestGameplaySystem::Instance(), &TestGameplaySystem::TestMouseDown);
	Griddy::Events::subscribe(PlayerController::Instance(), &PlayerController::onKeyDown);
	Griddy::Events::subscribe(PlayerController::Instance(), &PlayerController::onKeyUp);

	MainGame::Instance()->run();
	return 0;
}
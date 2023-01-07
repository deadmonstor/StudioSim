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

	//Slime
	for (int i = 0; i < 7; i++)
	{
		std::string currentString("shaders\\Blue-Slime-Idle\\tile00");
		currentString.append(std::to_string(i));
		currentString.append(".png");

		std::string currentStringID("BlueSlime00");
		currentStringID.append(std::to_string(i));

		ResourceManager::LoadTexture(currentString.c_str(), true, currentStringID);
	}

	//Slime Hurt
	for (int i = 0; i < 11; i++)
	{
		std::string currentString("shaders\\Blue-Slime-Hurt\\tile00");
		currentString.append(std::to_string(i));
		currentString.append(".png");

		std::string currentStringID("BlueSlimeHurt00");
		currentStringID.append(std::to_string(i));

		ResourceManager::LoadTexture(currentString.c_str(), true, currentStringID);
	}

	//Fireball
	for (int i = 0; i < 15; i++)
	{
		std::string currentString("shaders\\Fireball\\tile00");
		currentString.append(std::to_string(i));
		currentString.append(".png");

		std::string currentStringID("Fireball00");
		currentStringID.append(std::to_string(i));

		ResourceManager::LoadTexture(currentString.c_str(), true, currentStringID);
	}
	
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
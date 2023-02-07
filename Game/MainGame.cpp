#include "MainGame.h"
#include <Util/Logger.h>
#include "TestGameplaySystem.h"
#include "Components/Items/Armour/CommonArmour.h"
#include "Components/Items/Armour/LegendaryArmour.h"
#include "Components/Items/Armour/RareArmour.h"
#include "Components/Items/Consumables/ExpPotion.h"
#include "Components/Items/Consumables/HealthPotion.h"
#include "Components/Items/Consumables/ManaPotion.h"
#include "Components/Items/Spells/FireBallSpell.h"
#include "Components/Items/Spells/IceSpell.h"
#include "Components/Items/Weapons/CommonAxe.h"
#include "Components/Items/Weapons/CommonDagger.h"
#include "Components/Items/Weapons/CommonSword.h"
#include "Components/Items/Weapons/LegendaryHammer.h"
#include "Components/Items/Weapons/RareAxe.h"
#include "Components/Items/Weapons/RareSword.h"
#include "Core/Renderer/Renderer.h"
#include "Scenes/DefeatScene.h"
#include "Scenes/Level1Scene.h"
#include "Scenes/Level2Scene.h"
#include "Scenes/MainMenu.h"
#include "Scenes/VictoryScene.h"
#include "Scenes/ScoreScene.h"
#include "Scenes/LeaderboardScene.h"
#include "Util/Events/Events.h"
#include <Core/AudioEngine.h>

int main(int, char**)
{
	if (!MainGame::Instance()->init())
	{
		LOG_ERROR("Failed to initialize the game");
		return -1;
	}

	const auto Renderer = Renderer::Instance();
	Renderer->setWindowTitle("Into The Crypt");
	Renderer->setWindowIcon("Sprites\\icon.png");
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
	ResourceManager::LoadTextureArray("Sprites\\Crab\\", "crab", 16);
	ResourceManager::LoadTextureArray("Sprites\\player\\", "hero", 5);
	ResourceManager::LoadTextureArray("Sprites\\TileMap\\", "tile", 293);
	//Coins and chest
	ResourceManager::LoadTextureArray("Sprites\\Chest\\", "chest_", 4);
	ResourceManager::LoadTextureArray("Sprites\\Chest\\", "chest_open_", 4);
	ResourceManager::LoadTextureArray("Sprites\\Coins\\", "coin", 10);
	ResourceManager::LoadTextureArray("Sprites\\Weapons\\", "Potion", 3);
	ResourceManager::LoadTexture("Sprites\\whitetexture.png", "whitetexture");

	ResourceManager::LoadTexture("Sprites/Weapons/Axe.png", "Inventory-Axe");
	ResourceManager::LoadTexture("Sprites/Weapons/Sword.png", "Inventory-Sword");
	ResourceManager::LoadTexture("Sprites/Weapons/Dagger.png", "Inventory-Dagger");
	ResourceManager::LoadTexture("Sprites/Weapons/Hammer.png", "Inventory-Hammer");
	ResourceManager::LoadTexture("Sprites/Weapons/Spellbook1.png", "Inventory-IceSpell");
	ResourceManager::LoadTexture("Sprites/Weapons/Spellbook2.png", "Inventory-PoisonSpell");
	ResourceManager::LoadTexture("Sprites/Weapons/Spellbook4.png", "Inventory-FireSpell");
	ResourceManager::LoadTexture("Sprites/Armour/BasicArmourChest.png", "Inventory-BasicArmourChest");
	ResourceManager::LoadTexture("Sprites/Armour/MidArmourChest.png", "Inventory-MidArmourChest");
	ResourceManager::LoadTexture("Sprites/Armour/TopArmourChest.png", "Inventory-TopArmourChest");
	ResourceManager::LoadTexture("Sprites/Weapons/Potion0.png", "Inventory-Potion0");
	ResourceManager::LoadTexture("Sprites/Weapons/Potion1.png", "Inventory-Potion1");
	ResourceManager::LoadTexture("Sprites/Weapons/Potion2.png", "Inventory-Potion2");

	
	AudioEngine::Instance()->loadSound("Sounds\\MainTheme.wav", FMOD_3D);
	AudioEngine::Instance()->loadSound("Sounds\\Defeat.wav", FMOD_3D);
	AudioEngine::Instance()->loadSound("Sounds\\Victory.wav", FMOD_3D);
	AudioEngine::Instance()->loadSound("Sounds\\Click.wav", FMOD_3D);
	AudioEngine::Instance()->loadSound("Sounds\\AirSlash.wav", FMOD_3D);
	AudioEngine::Instance()->loadSound("Sounds\\Damage.wav", FMOD_3D);
	AudioEngine::Instance()->loadSound("Sounds\\softStep.wav", FMOD_3D);
	AudioEngine::Instance()->loadSound("Sounds\\FireBall.wav", FMOD_3D);
	AudioEngine::Instance()->loadSound("Sounds\\Ice.wav", FMOD_3D);

	SceneManager::Instance()->sceneToTypeID = std::map<std::string, std::function<Scene*()>>
	{
		{"mainMenu", []
			{
				return new MainMenu();
			}
		},
		{"level1", []
			{
				return new Level1Scene();
			}
		},
		{"level2", []
			{
				return new Level2Scene();
			}
		},
		{"victoryScreen", []
			{
				return new VictoryScene();
			}
		},
		{"defeatScreen", []
			{
				return new DefeatScene();
			}
		},
		{"scoreScene", []
			{
				return new ScoreScene();
			}		
		},
		{"leaderboardScene", []
			{
				return new LeaderboardScene();
			}
		},
	};

	// TODO: Is there a better way to do this? I don't like having to do this here
	Inventory::getItemByName =
	{
		// WEAPONS
		{"commonAxe", []() { return new CommonAxe(); }},
		{"commonDagger", []() { return new CommonDagger(); }},
		{"commonSword", []() { return new CommonSword(); }},
		{"legendaryHammer", []() { return new LegendaryHammer(); }},
		{"rareAxe", []() { return new RareAxe(); }},
		{"rareSword", []() { return new RareSword(); }},

		// SPELLS
		{"fireBallSpell", []() { return new FireBallSpell(); }},
		{"iceSpell", []() { return new IceSpell(); }},

		// CONSUMABLES
		{"healthPotion", []() { return new HealthPotion(); }},
		{"manaPotion", []() { return new ManaPotion(); }},
		{"expPotion", []() { return new ExpPotion(); }},
		
	    // Armour
		{"commonArmour", []() { return new CommonArmour(); }},
		{"rareArmour", []() { return new RareArmour(); }},
		{"legendaryArmour", []() { return new LegendaryArmour(); }},
	};
	MainGame::Instance()->run();
	return 0;
}
#include "Level2Scene.h"

#include "Core/SceneManager.h"
#include "Core/Components/Camera.h"
#include "Core/Components/TextRenderer.h"
#include "Core/Grid/GridSystem.h"
#include "Core/Renderer/Renderer.h"
#include "Util/Events/Events.h"
#include "../Components/TurnManager.h"
#include "../Tiles/TestTile.h"
#include "../Tiles/ChestTile.h"
#include "../Tiles/TeleportTile.h"
#include "../Components/Player/PlayerController.h"
#include "../Components/EnemyComponent.h"
#include "../Components/UI/HUD.h"
#include "Core/Components/Transform.h"
#include "../Tiles/SpikeTile.h"
#include "../Tiles/LightTile.h"
#include "../Tiles/BossRoomEntryTile.h"
#include "../LootTable.h"
#include "../Components/UI/InventoryHUD.h"
#include "Core/AudioEngine.h"
#include "Core/Components/AnimatedSpriteRenderer.h"
#include "../Components/AI Behaviours/Reaper/ReaperStateMachine.h"

void Level2Scene::createEnemy(const glm::vec2 pos)
{
	AudioEngine::Instance()->playSound("Sounds\\MainTheme.wav", false, 0.1f, 0, 0, AudioType::BackgroundMusic);
	
	const glm::vec2 tileWorldSpace = GridSystem::Instance()->getWorldPosition(pos);
	int random = rand() % 10000000;
	int randomEnemy = rand() % 2; //% by how many different types of enemies
	
	auto* enemy = SceneManager::Instance()->createGameObject("TestEnemy-" + std::to_string(random), tileWorldSpace);
	enemy->getTransform()->setSize(glm::vec2(35, 35));

	std::vector textureList = ResourceManager::GetTexturesContaining("SkeletonMove");
	

	StateMachine* fsm = enemy->addComponent<NormalEnemyFSM>();
	EnemyStats slimeStats = EnemyStats();
	switch (randomEnemy)
	{
	case 0:
		textureList = ResourceManager::GetTexturesContaining("SkeletonMove");

		slimeStats.attack = 4;
		slimeStats.critChance = 0.2f;
		slimeStats.maxHealth = 50;
		slimeStats.currentHealth = slimeStats.maxHealth;
		slimeStats.defence = 2;
		break;

	case 1:
		textureList = ResourceManager::GetTexturesContaining("ZombieMove");

		slimeStats.attack = 2;
		slimeStats.critChance = 0.4f;
		slimeStats.maxHealth = 80;
		slimeStats.currentHealth = slimeStats.maxHealth;
		slimeStats.defence = 4;
		break;

	default:
		textureList = ResourceManager::GetTexturesContaining("SkeletonMove");

		slimeStats.attack = 4;
		slimeStats.critChance = 0.2f;
		slimeStats.maxHealth = 50;
		slimeStats.currentHealth = slimeStats.maxHealth;
		slimeStats.defence = 2;
		//, "Blue-Slime-Idle"
		break;
	}
		
	auto sprite = enemy->addComponent<AnimatedSpriteRenderer>(textureList, 0.05f);
	sprite->setColor(glm::vec3(1, 1, 1));
	sprite->setLit(false);
	sprite->setPivot(Pivot::Center);
	
	EnemyComponent component = EnemyComponent(fsm, slimeStats);
	enemy->addComponent<EnemyComponent>(component);

	GridSystem::Instance()->setSatOnTile(0, pos, enemy);
}

void Level2Scene::createBoss(const glm::vec2 pos)
{
	//Reaper
	const glm::vec2 tileWorldSpace = GridSystem::Instance()->getWorldPosition(pos);
	auto* reaper = SceneManager::Instance()->createGameObject("Reaper", tileWorldSpace);
	reaper->getTransform()->setPosition(glm::vec2(tileWorldSpace.x, tileWorldSpace.y + 40));
	reaper->getTransform()->setSize(glm::vec2(144, 168));

	GridSystem::Instance()->setSatOnTile(0, pos, reaper);
	GridSystem::Instance()->setSatOnTile(0, pos + glm::vec2(0, 1), reaper);

	const std::vector textureListReaper = ResourceManager::GetTexturesContaining("GRI");
	auto sprite = reaper->addComponent<AnimatedSpriteRenderer>(textureListReaper, 0.075f);
	sprite->setPivot(Pivot::Center);
	sprite->setColor(glm::vec3(1, 1, 1));
	sprite->setLit(false);

	std::vector<glm::vec2> spawnerPositions;
	spawnerPositions.push_back(glm::vec2(30, 58));
	spawnerPositions.push_back(glm::vec2(30, 50));

	StateMachine* fsm = reaper->addComponent<ReaperStateMachine>(pos, spawnerPositions);
	EnemyStats bossStats = EnemyStats();
	bossStats.attack = 8;
	bossStats.critChance = 0.0f;
	bossStats.maxHealth = 150;
	bossStats.currentHealth = 150;
	bossStats.defence = 6;
	EnemyComponent component = EnemyComponent(fsm, bossStats);
	reaper->addComponent<EnemyComponent>(component);
}

void Level2Scene::init()
{
	LootTable::Instance()->LoadingIntoLootTableArray();
	
	auto backgroundSortingLayer = Renderer::addSortingLayer("Background Grid", -1);
	auto middleSortingLayer = Renderer::addSortingLayer("Middle Grid", 0);
	auto enemySortingLayer = Renderer::addSortingLayer("Top Grid", 1);

	GridSystem* grid_system = GridSystem::Instance();
	grid_system->init(glm::vec2(48, 48), glm::vec2(70, 70));
	grid_system->setOrderMap(
	{
		{0, backgroundSortingLayer},
		{1, middleSortingLayer},
		{2, enemySortingLayer},
	});
	
	grid_system->setEmptyTileIDs(0, std::vector<int>{0});
	grid_system->setWallIDs(0, std::vector<int>{1,9,3,4,5,6});
	grid_system->setTextureMap(0, std::map<int, Texture>
	{
		{ 1, ResourceManager::GetTexture("tile25")},
		{ 2, ResourceManager::GetTexture("tile218")},
		{ 3, ResourceManager::GetTexture("tile2")},
		{ 4, ResourceManager::GetTexture("tile4") },
		{ 5, ResourceManager::GetTexture("tile50") },
		{ 6, ResourceManager::GetTexture("tile28") },
		{ 7, ResourceManager::GetTexture("tile51") },
		{ 8, ResourceManager::GetTexture("tile204") },
		{ 9, ResourceManager::GetTexture("tile26") },
		{ 10, ResourceManager::GetTexture("tile33") }, //Stairs. 57 is lattice
		{ 11, ResourceManager::GetTexture("tile242") },
		{ 12, ResourceManager::GetTexture("tile57") },
		{ 13, ResourceManager::GetTexture("tile57") },
		{ 15, ResourceManager::GetTexture("tile57") },
		{ 19, ResourceManager::GetTexture("tile218") },
		{ 14, ResourceManager::GetTexture("tile270") }
	});
	std::vector<glm::vec2> bossEntranceTilePositions;
	bossEntranceTilePositions.push_back(glm::vec2(37, 49));
	bossEntranceTilePositions.push_back(glm::vec2(38, 49));

	std::vector<glm::vec2> bossPositionTiles;
	bossPositionTiles.push_back(glm::vec2(32, 53));
	bossPositionTiles.push_back(glm::vec2(32, 54));

	grid_system->setTileFunctionMap(0, std::map<int, std::function<Tile* ()>>
	{
		{ 13, [] { return new TeleportTile(Texture(), 61, 68); } }, //Change Values so aren't hard coded
		{ 14, [] { return new TestTile(Texture(), "victoryScreen", false); } },
		{ 19, [&] { return new BossRoomEntryTile(Texture(), "tile25", glm::vec2(37, 50), bossEntranceTilePositions, bossPositionTiles); } },
		{ 15, [] { return new TeleportTile(Texture(), 11, 54); } },
	});
	
	grid_system->loadFromFile(0, "Grid/SecondLevelDesign.txt");

		grid_system->setEmptyTileIDs(1, std::vector<int>{});
		grid_system->setWallIDs(1, std::vector<int>{35, 36, 41, 42, 43, 44, 31, 32, 33});
		grid_system->setTextureMap(1, std::map<int, Texture>
		{
			{ 21, ResourceManager::GetTexture("tile12")},//tile 12 above tile 36 // tile 11 above 35 // tile 13 above 37
			{ 22, ResourceManager::GetTexture("tile36") },//tile111 skulls
			{ 23, ResourceManager::GetTexture("tile11") },//tile223 rocks
			{ 24, ResourceManager::GetTexture("tile35") }, //Pillars : 20 44 68, 21 45 69, 22 46 70,
			{ 25, ResourceManager::GetTexture("tile13") }, //104 105
			{ 26, ResourceManager::GetTexture("tile37") }, //stair case/window
			{ 27, ResourceManager::GetTexture("tile111") }, //skulls
			{ 28, ResourceManager::GetTexture("tile223") }, //rocks
			{ 29, ResourceManager::GetTexture("tile20") },
			{ 30, ResourceManager::GetTexture("tile44") },
			{ 31, ResourceManager::GetTexture("tile68") },
			{ 32, ResourceManager::GetTexture("tile129") },	//vases
			{ 33, ResourceManager::GetTexture("tile153") },	//vases
			{ 34, ResourceManager::GetTexture("tile57") }, //lattice
			{ 35, ResourceManager::GetTexture("tile127") },
			{ 36, ResourceManager::GetTexture("tile151") },
			{ 37, ResourceManager::GetTexture("tile131") },
			{ 38, ResourceManager::GetTexture("tile155") },
			{ 39, ResourceManager::GetTexture("tile288") },
			{ 40, ResourceManager::GetTexture("tile289") },
			{ 41, ResourceManager::GetTexture("tile132") },
			{ 42, ResourceManager::GetTexture("tile133") },
			{ 43, ResourceManager::GetTexture("tile156") },
			{ 44, ResourceManager::GetTexture("tile157") },
			{ 45, ResourceManager::GetTexture("tile290") }, //bones
			{ 46, ResourceManager::GetTexture("tile291") }, //skulls
			{ 47, ResourceManager::GetTexture("tile73") }, //window with bars
			{ 48, ResourceManager::GetTexture("tile130") },//Jar
			{ 49, ResourceManager::GetTexture("tile154") },
			{ 56, ResourceManager::GetTexture("tile60") }, // Spike
			{ 93, ResourceManager::GetTexture("chest_2") }, //Chest
		});
		
		grid_system->setTileFunctionMap(1, std::map<int, std::function<Tile* ()>>
		{
			{ 37, [] { return new LightTile(Texture()); } },
			{ 56, [] { return new SpikeTile(Texture()); } },
			{ 93, [] { return new ChestTile(Texture()); } }
		});

	grid_system->loadFromFile(1, "Grid/SecondLevelDesignDetail.txt");

	grid_system->setEmptyTileIDs(2, std::vector<int>{});
	grid_system->setWallIDs(2, std::vector<int>{29, 35, 36, 41, 42, 43, 44, 32, 33});
	grid_system->setSpawnFunctionMap(2,
	{
		{ 91, [this](glm::vec2 pos)
		{
			PlayerController::Instance()->createPlayer();
			PlayerController::Instance()->playerPTR->getTransform()->setPosition(GridSystem::Instance()->getWorldPosition(pos));
		} },
		{ 92, [this](glm::vec2 pos)
		{
			createEnemy(pos);
		} },
		{ 98, [this](glm::vec2 pos)
		{
			createBoss(pos);
		} }
	});
	
	grid_system->loadFromFile(2, "Grid/SecondLevelDesignSP.txt");
	TurnManager::Instance()->startTurnSystem();
}

void Level2Scene::update()
{
	if (GridSystem::Instance()->isLoaded() && PlayerController::Instance()->playerPTR != nullptr)
	{
		if (!HUD::Instance()->getHasLoaded())
			HUD::Instance()->createHUD();

		HUD::Instance()->updateHUD();
	}

	if (GridSystem::Instance()->isLoaded() && PlayerController::Instance()->playerPTR != nullptr)
	{
		if (!InventoryHUD::Instance()->getHasLoaded())
			InventoryHUD::Instance()->createHUD();

		InventoryHUD::Instance()->updateHUD();
	}
}

void Level2Scene::destroy()
{
    
}
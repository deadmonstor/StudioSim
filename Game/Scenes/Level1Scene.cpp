#include "Level1Scene.h"

#include "TutorialScene.h"
#include "Core/SceneManager.h"
#include "Core/Components/Camera.h"
#include "Core/Components/TextRenderer.h"
#include "Core/Grid/GridSystem.h"
#include "Core/Renderer/Renderer.h"
#include "Util/Events/Events.h"
#include "../Components/TurnManager.h"
#include "../Tiles/TestTile.h"
#include "../Tiles/LightTile.h"
#include "../Components/Player/PlayerController.h"
#include "../Components/EnemyComponent.h"
#include "../ScoreSystem.h"
#include "../Components/UI/HUD.h"
#include "Core/Components/Transform.h"
#include "../Tiles/SpikeTile.h"
#include "../Tiles/BossRoomEntryTile.h"
#include "../LootTable.h"
#include "../Components/UI/InventoryHUD.h"
#include "../Tiles/ChestTile.h"
#include "Core/AudioEngine.h"
#include "Core/Components/AnimatedSpriteRenderer.h"
#include "../Components/DestroyAfterAnimation.h"
#include "../BossMusic.h"
#include "../Tiles/ShopTile.h"
#include "../AllItemInclude.h"

void Level1Scene::createSlime(const glm::vec2 pos)
{
	const glm::vec2 tileWorldSpace = GridSystem::Instance()->getWorldPosition(pos);
	int random = rand() % 10000000;
	int randomEnemy = rand() % 3;
		
	auto* enemy = SceneManager::Instance()->createGameObject("TestEnemy-" + std::to_string(random), tileWorldSpace);
	enemy->getTransform()->setSize(glm::vec2(48, 24));

	std::vector textureList = ResourceManager::GetTexturesContaining("Blue-Slime-Idle");

	StateMachine* fsm = enemy->addComponent<NormalEnemyFSM>();
	EnemyStats slimeStats = EnemyStats();
	switch (randomEnemy)
	{
		case 0:
			textureList = ResourceManager::GetTexturesContaining("Blue-Slime-Idle");

			slimeStats.attack = 2;
			slimeStats.critChance = 0.2f;
			slimeStats.maxHealth = 10;
			slimeStats.currentHealth = 10;
			slimeStats.defence = 2;
			slimeStats.deathEnemyList = ResourceManager::GetTexturesContaining("Blue-Slime-Death");
			break;

		case 1:
			textureList = ResourceManager::GetTexturesContaining("Red-Slime-Idle");

			slimeStats.attack = 3;
			slimeStats.critChance = 0.5f;
			slimeStats.maxHealth = 20;
			slimeStats.currentHealth = 20;
			slimeStats.defence = 1;
			slimeStats.deathEnemyList = ResourceManager::GetTexturesContaining("Red-Slime-Death");
			break;

		case 2:
			textureList = ResourceManager::GetTexturesContaining("Green-Slime-Idle");

			slimeStats.attack = 2;
			slimeStats.critChance = 0.2f;
			slimeStats.maxHealth = 15;
			slimeStats.currentHealth = 15;
			slimeStats.defence = 3;
			slimeStats.deathEnemyList = ResourceManager::GetTexturesContaining("Green-Slime-Death");
			//, "Green-Slime-Idle"
			break;

		default:
			textureList = ResourceManager::GetTexturesContaining("Blue-Slime-Idle");

			slimeStats.attack = 2;
			slimeStats.critChance = 0.2f;
			slimeStats.maxHealth = 10;
			slimeStats.currentHealth = 10;
			slimeStats.defence = 2;
			slimeStats.deathEnemyList = ResourceManager::GetTexturesContaining("Blue-Slime-Death");
			//, "Blue-Slime-Idle"
			break;
	}

	EnemyComponent component = EnemyComponent(fsm, slimeStats);
	auto sprite = enemy->addComponent<AnimatedSpriteRenderer>(textureList, 0.05f);
	sprite->setColor(glm::vec3(1, 1, 1));
	sprite->setLit(true);
	sprite->setPivot(Pivot::Center);

	//EnemyStats slimeStats = EnemyStats();
	//slimeStats.attack = 2;
	//slimeStats.critChance = 0.2f;
	//slimeStats.maxHealth = 25;
	//slimeStats.currentHealth = slimeStats.maxHealth;
	//slimeStats.defence = 2;
	//EnemyComponent component = EnemyComponent(fsm, slimeStats, "Blue-Slime-Idle");
	enemy->addComponent<EnemyComponent>(component);

	GridSystem::Instance()->setSatOnTile(0, pos, enemy);
}

void Level1Scene::createBoss(const glm::vec2 pos)
{
	//Crab
	const glm::vec2 tileWorldSpace = GridSystem::Instance()->getWorldPosition(pos);
	auto* Crab = SceneManager::Instance()->createGameObject("Crab", tileWorldSpace);
	Crab->getTransform()->setPosition(glm::vec2(tileWorldSpace.x + 20, tileWorldSpace.y - 28));
	Crab->getTransform()->setSize(glm::vec2(192, 192));

	GridSystem::Instance()->setSatOnTile(0, pos, Crab);
	GridSystem::Instance()->setSatOnTile(0, pos + glm::vec2(1, 0), Crab);

	BossMusic::Instance()->Initialise();

	const std::vector textureListCrab = ResourceManager::GetTexturesContaining("crab");
	auto sprite = Crab->addComponent<AnimatedSpriteRenderer>(textureListCrab, 0.075f);
	sprite->setPivot(Pivot::BottomCenter);
	sprite->setColor(glm::vec3(1, 1, 1));
	sprite->setLit(true);

	std::vector<glm::vec2> spawnerPositions;
	spawnerPositions.push_back(glm::vec2(17 ,18));
	spawnerPositions.push_back(glm::vec2(30, 18));

	StateMachine* fsm = Crab->addComponent<BossStateMachine>(pos, spawnerPositions);
	EnemyStats bossStats = EnemyStats();
	bossStats.attack = 4;
	bossStats.critChance = 0.15f;
	bossStats.maxHealth = 70;
	bossStats.currentHealth = 70;
	bossStats.defence = 5;
	EnemyComponent component = EnemyComponent(fsm, bossStats);
	Crab->addComponent<EnemyComponent>(component);
}

void Level1Scene::init()
{
	TutorialScene::hasCompletedTutorialLevel = true;
	

	AudioEngine::Instance()->playSound("Sounds\\MainTheme.wav", false, 0.1f, 0, 0, AudioType::BackgroundMusic);
	LootTable::Instance()->LoadingIntoLootTableArray();
	EnemyDropLootTable::Instance()->EnemyDropLoadingIntoLootTableArray();

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
		{ 10, ResourceManager::GetTexture("tile57") }, //Stairs. 57 is lattice
		{ 11, ResourceManager::GetTexture("tile242") },
		{ 19, ResourceManager::GetTexture("tile218") },
		{ 56, ResourceManager::GetTexture("tile218") } // Spike
	});
	std::vector<glm::vec2> bossEntranceTiles;
	bossEntranceTiles.push_back(glm::vec2(31, 23));
	bossEntranceTiles.push_back(glm::vec2(31, 22));
	bossEntranceTiles.push_back(glm::vec2(31, 21));

	std::vector<glm::vec2> bossPositionTiles;
	bossPositionTiles.push_back(glm::vec2(23, 18));
	bossPositionTiles.push_back(glm::vec2(24, 18));

	grid_system->setTileFunctionMap(0, std::map<int, std::function<Tile*()>>
	{
		{ 19, [&] { return new BossRoomEntryTile(Texture(), "tile26", glm::vec2(30, 22), bossEntranceTiles, bossPositionTiles); } },
		{ 10, [] { return new TestTile(Texture(), "level2", false); } },
		{ 56, [] { return new SpikeTile(Texture()); } }
	});
	
	grid_system->loadFromFile(0, "Grid/Test2.txt");
	
	grid_system->setEmptyTileIDs(1, std::vector<int>{});
	grid_system->setWallIDs(1, std::vector<int>{35, 36, 41, 42, 43, 44, 29, 30, 31, 32, 33});
	grid_system->setTextureMap(1, std::map<int, Texture>
	{
		{ 21, ResourceManager::GetTexture("tile12")},//tile 12 above tile 36 // tile 11 above 35 // tile 13 above 37
		{ 22, ResourceManager::GetTexture("tile36")},//tile111 skulls
		{ 23, ResourceManager::GetTexture("tile11")},//tile223 rocks
		{ 24, ResourceManager::GetTexture("tile35")}, //Pillars : 20 44 68, 21 45 69, 22 46 70,
		{ 25, ResourceManager::GetTexture("tile13")}, //104 105
		{ 26, ResourceManager::GetTexture("tile37")}, //stair case/window
		{ 27, ResourceManager::GetTexture("tile111")}, //skulls
		{ 28, ResourceManager::GetTexture("tile223")}, //rocks
		{ 29, ResourceManager::GetTexture("tile20")},
		{ 30, ResourceManager::GetTexture("tile44")},
		{ 31, ResourceManager::GetTexture("tile68")},
		{ 32, ResourceManager::GetTexture("tile129")},	//vases
		{ 33, ResourceManager::GetTexture("tile153")},	//vases
		{ 34, ResourceManager::GetTexture("tile57") }, //lattice
		{ 35, ResourceManager::GetTexture("tile127") },//barrels
		{ 36, ResourceManager::GetTexture("tile151") },
		{ 37, ResourceManager::GetTexture("tile131") },
		{ 38, ResourceManager::GetTexture("tile155") },
		{ 39, ResourceManager::GetTexture("tile288") },
		{ 40, ResourceManager::GetTexture("tile289") },
		{ 41, ResourceManager::GetTexture("tile132") },
		{ 42, ResourceManager::GetTexture("tile133") },
		{ 43, ResourceManager::GetTexture("tile156") },
		{ 44, ResourceManager::GetTexture("tile157") },
		{ 45, ResourceManager::GetTexture("tile290") }, //skulls
		{ 46, ResourceManager::GetTexture("tile291") }, //skulls
		{ 47, ResourceManager::GetTexture("tile73") }, //window with bars
		{ 48, ResourceManager::GetTexture("tile130") },//Jar
		{ 49, ResourceManager::GetTexture("tile154") },
		{ 56, ResourceManager::GetTexture("tile60") }, // Spike
		{ 93, ResourceManager::GetTexture("chest_2") }, //Chest
	});
	
	grid_system->setTileFunctionMap(1, std::map<int, std::function<Tile*()>>
	{
		{ 37, [] { return new LightTile(Texture()); } },
		{ 56, [] { return new SpikeTile(Texture()); } },
		{ 93, [] { return new ChestTile(Texture()); } },
		//{ 95, [] {return new ShopTile(Texture(), new LegendaryArmour());  } }
	});
	
	grid_system->loadFromFile(1, "Grid/LvlLayer2.txt");

	grid_system->setEmptyTileIDs(2, std::vector<int>{});
	grid_system->setWallIDs(2, std::vector<int>{});
	grid_system->setTileFunctionMap(2, std::map<int, std::function<Tile* ()>>
	{
		{ 95, [] {return new ShopTile(Texture(), new FireBallSpell());  } },
		{ 96, [] {return new ShopTile(Texture(), new IceSpell());  } },
		{ 97, [] {return new ShopTile(Texture(), new RareArmour());  } }
	});
	grid_system->setSpawnFunctionMap(2,
	{
		{ 91, [this](glm::vec2 pos)
		{
			PlayerController::Instance()->createPlayer();
			PlayerController::Instance()->playerPTR->getTransform()->setPosition(GridSystem::Instance()->getWorldPosition(pos));
		} },
		{ 92, [this](glm::vec2 pos)
		{
			createSlime(pos);
		} },
		{ 98, [this](glm::vec2 pos)
		{
				createBoss(pos);
		} }
	});
	
	grid_system->loadFromFile(2, "Grid/LevelDesignSP.txt");

	int m_count = 0;
	if (m_count == 1)
	{
		ScoreSystem::Instance()->ReadScores(false);
		m_count++;
	}

	if (m_count == 2)
	{
		ScoreSystem::Instance()->RenderTopScores();
	}
	
	TurnManager::Instance()->startTurnSystem();
}

void Level1Scene::update()
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

void Level1Scene::destroy()
{
    
}

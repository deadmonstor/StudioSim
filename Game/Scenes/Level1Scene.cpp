#include "Level1Scene.h"

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
#include "../LootTable.h"

void Level1Scene::createEnemy(const glm::vec2 pos)
{
	const glm::vec2 tileWorldSpace = GridSystem::Instance()->getWorldPosition(pos);
		
	auto* enemy = SceneManager::Instance()->createGameObject("TestEnemy", tileWorldSpace);
	enemy->getTransform()->setSize(glm::vec2(48, 24));
	enemy->addComponent<EnemyComponent>();

	GridSystem::Instance()->setSatOnTile(0, pos, enemy);
}

void Level1Scene::init()
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
	// TODO: Fill these out lol
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
		{ 56, ResourceManager::GetTexture("tile218") } // Spike
	});
	grid_system->setTileFunctionMap(0, std::map<int, std::function<Tile*()>>
	{
		{ 10, [] { return new TestTile(Texture(), "level2"); } },
		{ 56, [] { return new SpikeTile(Texture()); } }
	});
	
	grid_system->loadFromFile(0, "Grid/Test2.txt");
	
	grid_system->setEmptyTileIDs(1, std::vector<int>{});
	grid_system->setWallIDs(1, std::vector<int>{35, 36, 41, 42, 43, 44, 31, 32, 33});
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
		{ 56, ResourceManager::GetTexture("tile60") } // Spike
	});
	grid_system->setTileFunctionMap(1, std::map<int, std::function<Tile*()>>
	{
		{ 37, [] { return new LightTile(Texture()); } },
	});
	
	grid_system->loadFromFile(1, "Grid/LvlLayer2.txt");

	grid_system->setEmptyTileIDs(2, std::vector<int>{});
	grid_system->setWallIDs(2, std::vector<int>{});
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
		{ 93, [this](glm::vec2 pos)
		{
			// TODO: Create a chest
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
}

void Level1Scene::destroy()
{
    
}

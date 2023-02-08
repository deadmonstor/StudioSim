#include "CreditsScene.h"

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
#include "../Components/UI/HUD.h"
#include "Core/Components/Transform.h"
#include "../Tiles/SpikeTile.h"
#include "../LootTable.h"
#include "../Components/UI/InventoryHUD.h"
#include "../Tiles/ChestTile.h"
#include "Core/AudioEngine.h"
#include "Core/Components/AnimatedSpriteRenderer.h"



void CreditsScene::init()
{
	engineRenderID = Griddy::Events::subscribe(this, &CreditsScene::onEngineRender);
	
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
	});
	std::vector<glm::vec2> bossEntranceTiles;
	bossEntranceTiles.push_back(glm::vec2(31, 23));
	bossEntranceTiles.push_back(glm::vec2(31, 22));
	bossEntranceTiles.push_back(glm::vec2(31, 21));
	grid_system->setTileFunctionMap(0, std::map<int, std::function<Tile*()>>
	{
		{ 10, [] { return new TestTile(Texture(), "mainMenu", true); } },
	});
	
	grid_system->loadFromFile(0, "Grid/TutorialLevelDesign.txt");
	
	grid_system->setEmptyTileIDs(1, std::vector<int>{});
	grid_system->setWallIDs(1, std::vector<int>{});
	grid_system->setTextureMap(1, std::map<int, Texture> {});
	
	grid_system->setTileFunctionMap(1, std::map<int, std::function<Tile*()>>
	{

	});
	
	grid_system->loadFromFile(1, "Grid/TutorialLevelDesignDetail.txt");

	grid_system->setEmptyTileIDs(2, std::vector<int>{});
	grid_system->setWallIDs(2, std::vector<int>{});
	grid_system->setSpawnFunctionMap(2,
	{
		{ 91, [this](glm::vec2 pos)
		{
			PlayerController::Instance()->createPlayer();
			PlayerController::Instance()->playerPTR->getTransform()->setPosition(GridSystem::Instance()->getWorldPosition(pos));
		} }
	});
	
	grid_system->loadFromFile(2, "Grid/TutorialLevelDesignSP.txt");
	TurnManager::Instance()->startTurnSystem();
}

void CreditsScene::update()
{
	if (hasCompletedTutorialLevel)
	{
		SceneManager::Instance()->changeScene("mainMenu");
	}
	
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

void CreditsScene::renderTextOutlined(const glm::vec2 worldPosition,
	const std::string& text,
	const float scale,
	const float outlineThickness,
	const glm::vec3& color,
	const glm::vec3& colorOutline)
{
	renderText(worldPosition, text, scale - outlineThickness, colorOutline);
	renderText(worldPosition, text, scale, color);
}

void CreditsScene::renderText(const glm::vec2 worldPosition, const std::string& text, const float scale, const glm::vec3& color)
{
	const glm::vec2 sizeOfText = TextRenderer::Instance()->renderTextSize(text, scale);
	TextRenderer::Instance()->renderText(text,
		worldPosition.x - Renderer::Instance()->getCameraPosScreenSpace().x - sizeOfText.x / 2,
		worldPosition.y - Renderer::Instance()->getCameraPosScreenSpace().y - sizeOfText.y / 2,
		scale,
		color,
		glm::vec2{0.5f, 0.5f}
	);
}

void CreditsScene::onEngineRender(const OnEngineRender* event)
{
	auto pos = PlayerController::Instance()->playerPTR->getTransform()->getPosition();

	// TODO: POC
	renderTextOutlined(
		{ pos.x, 2208},
		"Credits",
		1.0f,
		-0.0075f,
		{1, 1, 1},
		{0,0,0}
	);
	
	renderText({200, 1968}, "Lewis Powell", 0.5f, {1, 1, 1});
	renderText({ 400, 1968 }, "Josh Mobley", 0.5f, { 1, 1, 1 });
	renderText({ 600, 1968 }, "Szymon Sadunski", 0.5f, { 1, 1, 1 });
	renderText({ 800, 1968 }, "Pablo Cano San Roman", 0.5f, { 1, 1, 1 });
	renderText({ 1000, 1968 }, "Conner Pittway", 0.5f, { 1, 1, 1 });
	renderText({ 1200, 1968 }, "Charlotte Marriner", 0.5f, { 1, 1, 1 });
	renderText({ 1400, 1968 }, "Tolu Arowolo", 0.5f, { 1, 1, 1 });
	renderText({ 1600, 1968 }, "Fayzaan Ali", 0.5f, { 1, 1, 1 });
	renderText({ 1800, 1968 }, "Lee Hall", 0.5f, { 1, 1, 1 });

	renderText({ 2100, 1968 }, "Special Mentions: Chris, The Brandons, and Group 4", 0.5f, { 1, 1, 1 });
	renderText({ 2500, 1968 }, "Special Mentions: Jimmy", 0.5f, { 1, 1, 1 });
	renderText({ 2900, 1968 }, "Special Mentions: The Ember Lounge Lecturers", 0.5f, { 1, 1, 1 });
	//renderText({ 2600, 1968 }, "Special Mentions: ", 0.5f, { 1, 1, 1 });

	
}

void CreditsScene::destroy()
{
	Griddy::Events::unsubscribe(this, &CreditsScene::onEngineRender, engineRenderID);
}

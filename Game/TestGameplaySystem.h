﻿#pragma once
#include "Input.h"
#include "Components/FireballComponent.h"
#include "Core/SceneManager.h"
#include "Core/Components/AnimatedSpriteRenderer.h"
#include "Core/Components/TextRenderer.h"
#include "Core/Components/Transform.h"
#include "Core/Grid/GridSystem.h"
#include "Core/Renderer/ResourceManager.h"
#include "System/Inventory.h"
#include "Util/SingletonTemplate.h"
#include "Util/Time.h"
#include "Util/Events/EngineEvents.h"
#include "TurnManager.h"

class TestGameplaySystem : public SingletonTemplate<TestGameplaySystem>
{
public:
	std::list<SpriteComponent*> sprites;
	void testGameObjectDestroy(const OnGameObjectRemoved* event)
	{
		const auto gameObject = event->gameObject;
		const auto it = std::ranges::find_if(sprites, [gameObject](const SpriteComponent* sprite)
		{
			return sprite->getOwner() == gameObject;
		});
		
		if (it != sprites.end())
		{
			sprites.erase(it);
		}
	}
	void TestFunc(const OnSceneChanged* event)
	{
		// TODO: Enum this or something its kinda bad to do this
		if (event->key != "renderScene")
			return;

		GameObject* test = SceneManager::Instance()->createGameObject("Background", glm::vec2{-(1920 / 2), -(1080 / 2)});
		test->getTransform()->setSize(glm::vec2(1920 * 2, 1080 * 2));
		SpriteComponent* sprite = test->addComponent<SpriteComponent>();
		sprite->setTexture(ResourceManager::GetTexture("background"));
		sprite->setColor(glm::vec3(1, 1, 1));
		
		auto sortingLayer = Renderer::addSortingLayer("background", -2);
		sprite->setSortingLayer(sortingLayer);

		auto troll = SceneManager::Instance()->createGameObject("troll", glm::vec2 { -855, -540 + 127  });
		troll->getTransform()->setSize(glm::vec2(339, 26));

		auto trollsprite = troll->addComponent<SpriteComponent>();
		trollsprite->setLit(false);
		trollsprite->setTexture(ResourceManager::GetTexture("troll"));
		trollsprite->setColor(glm::vec3(1, 1, 1));
		sprites.push_back(trollsprite);
		sortingLayer = Renderer::addSortingLayer("troll sorting layer", 3);
		trollsprite->setSortingLayer(sortingLayer);

		sortingLayer = Renderer::addSortingLayer("middle", -1);
		
		for (int y = 0; y < 10; y++)
		{
			// Get random position
			float x = 400 - rand() % 1920;
			float yy = 400 - y;
			
			test = SceneManager::Instance()->createGameObject("Test-" + std::to_string(y), glm::vec2 { x, yy });
			test->getTransform()->setSize(glm::vec2(100,100));

			// pick a random texture between these 2
			const int textureIndex = rand() % 2;

			sprite = test->addComponent<SpriteComponent>();
			sprite->setColor(glm::vec3(1,1,1));
			sprite->setTexture(ResourceManager::GetTexture(textureIndex == 0 ? "face" : "face2"));
			sprite->setSortingLayer(sortingLayer);
		}

		test = SceneManager::Instance()->createGameObject("TestBlue-Slime-Idle Idle", glm::vec2{100, 100});
		test->getTransform()->setSize(glm::vec2(96, 48));

		const auto cam = test->addComponent<Camera>();
		Renderer::Instance()->setCamera(cam);
		const std::vector textureList = ResourceManager::GetTexturesContaining("Blue-Slime-Idle");
		sprite = test->addComponent<AnimatedSpriteRenderer>(textureList, 0.05f);
        sprite->setColor(glm::vec3(1, 1, 1));
        sprites.push_back(sprite);
	}
	
	void CreateFireball(glm::vec2 mousePos)
	{
		mousePos.x = mousePos.x;
		mousePos.y = mousePos.y;
		
		auto* fireball = SceneManager::Instance()->createGameObject("TestFireball", mousePos);
		fireball->getTransform()->setSize(glm::vec2(48, 48));
		fireball->addComponent<FireballComponent>();
	}
	
	void TestFuncLewis(const OnSceneChanged* event) 
	{
		// TODO: Enum this or something its kinda bad to do this
		if (event->key != "debugScene")
			return;

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
			{ 10, ResourceManager::GetTexture("tile57") },
			{ 11, ResourceManager::GetTexture("tile242") }
		});
		
		grid_system->loadFromFile(0, "Grid/test2.txt");
		
		grid_system->setEmptyTileIDs(1, std::vector<int>{});
		grid_system->setWallIDs(1, std::vector<int>{});
		grid_system->setTextureMap(1, std::map<int, Texture>
		{
			{ 21, ResourceManager::GetTexture("tile12")},//tile 12 above tile 36 // tile 11 above 35 // tile 13 above 37
			{ 22, ResourceManager::GetTexture("tile36")},//tile111 skulls
			{ 23, ResourceManager::GetTexture("tile11")},//tile223 rocks
			{ 24, ResourceManager::GetTexture("tile35")}, //Pillars : 20 44 68, 21 45 69, 22 46 70,
			{ 25, ResourceManager::GetTexture("tile13")}, //104 105
			{ 26, ResourceManager::GetTexture("tile37")},
			{ 27, ResourceManager::GetTexture("tile111")},
			{ 28, ResourceManager::GetTexture("tile223")},
			{ 29, ResourceManager::GetTexture("tile20")},
			{ 30, ResourceManager::GetTexture("tile44")},
			{ 31, ResourceManager::GetTexture("tile68")}
		});
		
		grid_system->loadFromFile(1, "Grid/LvlLayer2.txt");

		auto *test = SceneManager::Instance()->createGameObject("TestBlue-Slime-Idle Idle", glm::vec2{100, 100});
		test->getTransform()->setSize(glm::vec2(96, 48));

		const std::vector textureList = ResourceManager::GetTexturesContaining("Blue-Slime-Idle");
		auto sprite = test->addComponent<AnimatedSpriteRenderer>(textureList, 0.05f);
		sprite->setColor(glm::vec3(1, 1, 1));
		sprite->setLit(false);
		
		//Slime Hurt Anim
		auto* testHurt = SceneManager::Instance()->createGameObject("TestBlue-Slime-Idle Hurt", glm::vec2{ 300, 300 });
		testHurt->getTransform()->setSize(glm::vec2(96, 48));

		const std::vector textureListHurt = ResourceManager::GetTexturesContaining("Blue-Slime-Hurt");
		sprite = testHurt->addComponent<AnimatedSpriteRenderer>(textureListHurt, 0.05f);
		sprite->setColor(glm::vec3(1, 1, 1));
		sprite->setLit(false);

		//Slime Death Animation
		auto *testDeath = SceneManager::Instance()->createGameObject("Blue-Slime-Death", glm::vec2{350, 350});
		testDeath->getTransform()->setSize(glm::vec2(96, 48));

		const std::vector textureListDeath = ResourceManager::GetTexturesContaining("Blue-Slime-Death");
		sprite = testDeath->addComponent<AnimatedSpriteRenderer>(textureListDeath, 0.05f);
		sprite->setColor(glm::vec3(1, 1, 1));
		sprite->setLit(false);
		
		//Add zombie and skeleton

		//Zombie Animation
		auto *testZombie = SceneManager::Instance()->createGameObject("Zombie", glm::vec2{400, 400});
		testZombie->getTransform()->setSize(glm::vec2(38, 38));

		const std::vector textureListZombie = ResourceManager::GetTexturesContaining("Zombie");
		sprite = testZombie->addComponent<AnimatedSpriteRenderer>(textureListZombie, 0.05f);
		sprite->setColor(glm::vec3(1, 1, 1));
		sprite->setLit(false);
		

		//Skeleton Animation
		auto *testSkeleton = SceneManager::Instance()->createGameObject("Skeleton", glm::vec2{350, 400});
		testSkeleton->getTransform()->setSize(glm::vec2(38, 38));


		const std::vector textureListSkeleton = ResourceManager::GetTexturesContaining("Skeleton");
		sprite = testSkeleton->addComponent<AnimatedSpriteRenderer>(textureListSkeleton, 0.05f);
		sprite->setColor(glm::vec3(1, 1, 1));
		sprite->setLit(false);

		//FX1
		auto *testFX1 = SceneManager::Instance()->createGameObject("FX1", glm::vec2{350, 500});
		testFX1->getTransform()->setSize(glm::vec2(64, 64));

		const std::vector textureListFX1 = ResourceManager::GetTexturesContaining("FXSCircle");
		sprite = testFX1->addComponent<AnimatedSpriteRenderer>(textureListFX1, 0.05f);
		sprite->setColor(glm::vec3(1, 1, 1));
		sprite->setLit(false);
		//FX2
		auto *testFX2 = SceneManager::Instance()->createGameObject("FX2", glm::vec2{420, 500});
		testFX2->getTransform()->setSize(glm::vec2(64, 64));

		const std::vector textureListFX2 = ResourceManager::GetTexturesContaining("FXSDrop");
		sprite = testFX2->addComponent<AnimatedSpriteRenderer>(textureListFX2, 0.05f);
		sprite->setColor(glm::vec3(1, 1, 1));
		sprite->setLit(false);
		//FX3
		auto *testFX3 = SceneManager::Instance()->createGameObject("FX3", glm::vec2{280, 500});
		testFX3->getTransform()->setSize(glm::vec2(64, 64));

		const std::vector textureListFX3 = ResourceManager::GetTexturesContaining("FXSExpl");
		sprite = testFX3->addComponent<AnimatedSpriteRenderer>(textureListFX3, 0.05f);
		sprite->setColor(glm::vec3(1, 1, 1));
		sprite->setLit(false);

		//Red-Slash-Thin
		auto *testRST = SceneManager::Instance()->createGameObject("Red-Slash-Thin", glm::vec2{280, 700});
		testRST->getTransform()->setSize(glm::vec2(55, 40));

		const std::vector textureListRST = ResourceManager::GetTexturesContaining("RedSlashThin");
		sprite = testRST->addComponent<AnimatedSpriteRenderer>(textureListRST, 0.05f);
		sprite->setColor(glm::vec3(1, 1, 1));
		sprite->setLit(false);

		//Red-Slash-Wide
		auto *testRSW = SceneManager::Instance()->createGameObject("Red-Slash-Wide", glm::vec2{480, 700});
		testRSW->getTransform()->setSize(glm::vec2(55, 40));

		const std::vector textureListRSW = ResourceManager::GetTexturesContaining("Red-Slash-Wide");
		sprite = testRSW->addComponent<AnimatedSpriteRenderer>(textureListRSW, 0.05f);
		sprite->setColor(glm::vec3(1, 1, 1));
		sprite->setLit(false);

		TurnManager::Instance()->addToTurnQueue(testRST);
		TurnManager::Instance()->addToTurnQueue(testRSW);

		////Player Idle Anim
		auto *testPlayerIdle = SceneManager::Instance()->createGameObject("Player", glm::vec2{820, 540});
		testPlayerIdle->getTransform()->setSize(glm::vec2(40, 40));
		Light* playerLight = testPlayerIdle->addComponent<Light>();
		playerLight->setFalloff({1, 1, 5});
		auto cam = testPlayerIdle->addComponent<Camera>();
		Renderer::Instance()->setCamera(cam);
		
		const std::vector textureListPlayer = ResourceManager::GetTexturesContaining("hero");
		sprite = testPlayerIdle->addComponent<AnimatedSpriteRenderer>(textureListPlayer, 0.075f);
		sprite->setColor(glm::vec3(1, 1, 1));
		sprite->setLit(true);
		sprite->setPivot(Pivot::BottomCenter);
		sprites.push_back(sprite);
		
		//CreateFireball(glm::vec2{ 1000, 500 });
	}

	void TestInventory(const OnSceneChanged* event)
	{
		// TODO: Enum this or something its kinda bad to do this
		if (event->key != "testInventory")
			return;

		Inventory myInventory(50); // Holds 10 items
	
		Item sword;
		sword.name = "Bandit sword";
		sword.type = "Weapon";
		sword.itemDescription = "A common sword";
		sword.equipSlot = "Hand";
		sword.isEquipped = false;
		sword.atk = 10;
		sword.crit = 2;
		myInventory.add_item(sword);

		Item armour;
		armour.name = "Bandit armor";
		armour.type = "Armour";
		armour.equipSlot = "Chest";
		armour.isEquipped = false;
		armour.def = 15;
		myInventory.add_item(armour);

		Item spell;
		spell.name = "Fireball";
		spell.type = "Spell";
		spell.equipSlot = "Spells";
		spell.isEquipped = false;
		spell.spellAtk = 20;
		spell.manaCost = 10;
		spell.coolDown = 4; //Secods
		spell.effectDuration = 3; //Seconds
		myInventory.add_item(spell);

		myInventory.draw_inventory();
		myInventory.equip_item("Bandit sword");
		myInventory.draw_inventory();
	
		myInventory.equip_item("Fireball");
		myInventory.unequip_item("Bandit sword");
		myInventory.draw_inventory();
	}
	
	glm::fvec2 direction = glm::fvec2(0, 0);
	void TestFuncUpdate(OnEngineUpdate*)
	{
		// Update all sprites color to be a random color
		for (const auto& sprite : sprites)
		{
			if (sprite == nullptr || sprite->getOwner() == nullptr) continue;
			Transform* transform = sprite->getOwner()->getTransform();
			transform->setPosition(transform->getPosition() + direction * static_cast<float>(100.0f * Time::getDeltaTime()));
		}
	}

	void testRender(OnEngineRender*)
	{
		if (SceneManager::Instance()->getScene()->name != "testInventory")
			return;
		
		TextRenderer::Instance()->renderText("abcdefghijklmnopqrstuvwsyz", 500, 500, 1, glm::vec3(1, 1, 1));
	}
	
	void TestMouseDown(const OnMouseDown* mouseDownEvent)
	{
		const glm::vec2 mousePos = Input::getMousePosition();
		
		if (mouseDownEvent->key == GLFW_MOUSE_BUTTON_3)
			CreateFireball(mousePos);
	}
	void testKeyDown(const OnKeyDown* keyDown)
	{
		if (keyDown->key == GLFW_KEY_W)
		{
			direction.y += 1;
		}
		else if (keyDown->key == GLFW_KEY_S)
		{
			direction.y -= 1;
		}
		else if (keyDown->key == GLFW_KEY_A)
		{
			direction.x -= 1;
		}
		else if (keyDown->key == GLFW_KEY_D)
		{
			direction.x += 1;
		}
	}
	
	void testKeyUp(const OnKeyUp* keyUp)
	{
		if (keyUp->key == GLFW_KEY_W)
		{
			direction.y -= 1;
		}
		else if (keyUp->key == GLFW_KEY_S)
		{
			direction.y += 1;
		}
		else if (keyUp->key == GLFW_KEY_A)
		{
			direction.x += 1;
		}
		else if (keyUp->key == GLFW_KEY_D)
		{
			direction.x -= 1;
		}
	}
	
	void testDropCallback(const OnFileDropCallback* dropCallback)
	{
		LOG_INFO(dropCallback->count);
		glm::ivec2 mousePos = Input::getMousePosition();
		mousePos.x = mousePos.x - 24;
		mousePos.y = mousePos.y - 24;
		
		for (int i = 0; i < dropCallback->count; i++)
		{
			const Texture texture = ResourceManager::LoadTexture(dropCallback->paths[i], dropCallback->paths[i]);
		
			auto* fireball = SceneManager::Instance()->createGameObject(dropCallback->paths[i], mousePos);
			fireball->getTransform()->setSize(glm::vec2(texture.Width, texture.Height));

			const std::vector textureListFireball = ResourceManager::GetTexturesContaining(dropCallback->paths[i]);
			const auto sprite = fireball->addComponent<AnimatedSpriteRenderer>(textureListFireball, 0.05f);
			sprite->setColor(glm::vec3(1, 1, 1));

			mousePos.x = mousePos.x - texture.Width;
			mousePos.y = mousePos.y - texture.Height;
		}
	}
};

#pragma once
#include "Input.h"
#include "Components/FireballComponent.h"
#include "Core/SceneManager.h"
#include "Core/Components/AnimatedSpriteRenderer.h"
#include "Core/Components/Transform.h"
#include "Core/Grid/GridSystem.h"
#include "Core/Renderer/ResourceManager.h"
#include "Util/SingletonTemplate.h"
#include "Util/Time.h"
#include "Util/Events/EngineEvents.h"

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
		test->getTransform()->SetScale(glm::vec2(1920 * 1.3, 1080 * 1.3));
		SpriteComponent* sprite = test->addComponent<SpriteComponent>();
		sprite->setTexture(ResourceManager::GetTexture("background"));
		sprite->setColor(glm::vec3(1, 1, 1));
		sprites.push_back(sprite);
		
		auto sortingLayer = Renderer::addSortingLayer("background", -2);
		sprite->setSortingLayer(sortingLayer);

		auto troll = SceneManager::Instance()->createGameObject("troll", glm::vec2 { -855, -540 + 127  });
		troll->getTransform()->SetScale(glm::vec2(339, 26));

		auto trollsprite = troll->addComponent<SpriteComponent>();
		trollsprite->setLit(false);
		trollsprite->setTexture(ResourceManager::GetTexture("troll"));
		trollsprite->setColor(glm::vec3(1, 1, 1));
		sprites.push_back(trollsprite);
		sortingLayer = Renderer::addSortingLayer("troll sorting layer", 3);
		trollsprite->setSortingLayer(sortingLayer);

		sortingLayer = Renderer::addSortingLayer("middle", -1);
		
		for (int y = 0; y < 100; y++)
		{
			// Get random position
			float x = 400 - rand() % 1920;
			float yy = 400 - rand() % 1080;
			
			test = SceneManager::Instance()->createGameObject("Test-1", glm::vec2 { x, yy });
			test->getTransform()->SetScale(glm::vec2(100,100));

			// pick a random texture between these 2
			const int textureIndex = rand() % 2;

			sprite = test->addComponent<SpriteComponent>();
			sprite->setColor(glm::vec3(1,1,1));
			sprite->setTexture(ResourceManager::GetTexture(textureIndex == 0 ? "face" : "face2"));
			sprite->setSortingLayer(sortingLayer);
		}

		test = SceneManager::Instance()->createGameObject("TestBlue-Slime-Idle Idle", glm::vec2{100, 100});
		test->getTransform()->SetScale(glm::vec2(96, 48));
		
		auto cam = test->addComponent<Camera>();
		Renderer::Instance()->setCamera(cam);
		const std::vector textureList = ResourceManager::GetTexturesContaining("Blue-Slime-Idle");
		sprite = test->addComponent<AnimatedSpriteRenderer>(textureList, 0.05f);
        sprite->setColor(glm::vec3(1, 1, 1));
        sprites.push_back(sprite);
	}
	
	void CreateFireball(glm::vec2 mousePos)
	{
		mousePos.x = mousePos.x -24;
		mousePos.y = mousePos.y - 24;
		
		auto* fireball = SceneManager::Instance()->createGameObject("TestFireball", mousePos);
		fireball->getTransform()->SetScale(glm::vec2(48, 48));
		fireball->addComponent<FireballComponent>();
	}
	
	void TestFuncLewis(const OnSceneChanged* event) 
	{
		// TODO: Enum this or something its kinda bad to do this
		if (event->key != "debugScene")
			return;
		
		GridSystem::Instance()->init(glm::vec2(96, 48), glm::vec2(100, 100));
		
		auto *background = SceneManager::Instance()->createGameObject("Background", glm::vec2{0, 0});
		background->getTransform()->SetScale(glm::vec2(300 * 3, 225 * 3));
		auto sprite = background->addComponent<SpriteComponent>();
		sprite->setColor(glm::vec3(1,1,1));
		sprite->setTexture(ResourceManager::GetTexture("rock"));
		
		auto *test = SceneManager::Instance()->createGameObject("TestBlue-Slime-Idle Idle", glm::vec2{100, 100});
		test->getTransform()->SetScale(glm::vec2(96, 48));
		
		auto cam = test->addComponent<Camera>();
		Renderer::Instance()->setCamera(cam);

		const std::vector textureList = ResourceManager::GetTexturesContaining("Blue-Slime-Idle");
		sprite = test->addComponent<AnimatedSpriteRenderer>(textureList, 0.05f);
		sprite->setColor(glm::vec3(1, 1, 1));
		sprites.push_back(sprite);

		auto* testHurt = SceneManager::Instance()->createGameObject("TestBlue-Slime-Idle Hurt", glm::vec2{ 300, 300 });
		testHurt->getTransform()->SetScale(glm::vec2(96, 48));

		const std::vector textureListHurt = ResourceManager::GetTexturesContaining("Blue-Slime-Hurt");
		sprite = testHurt->addComponent<AnimatedSpriteRenderer>(textureListHurt, 0.05f);
		sprite->setColor(glm::vec3(1, 1, 1));
			
		CreateFireball(glm::vec2{ 1000, 500 });
	}

	glm::fvec2 direction = glm::fvec2(0, 0);
	void TestFuncUpdate(OnEngineUpdate*)
	{
		// Update all sprites color to be a random color
		for (const auto& sprite : sprites)
		{
			if (sprite == nullptr || sprite->getOwner() == nullptr) continue;
			Transform* transform = sprite->getOwner()->getTransform();
			transform->SetPosition(transform->GetPosition() + direction * static_cast<float>(100.0f * Time::getDeltaTime()));
		}
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
			direction.y -= 1;
		}
		else if (keyDown->key == GLFW_KEY_S)
		{
			direction.y += 1;
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
			direction.y += 1;
		}
		else if (keyUp->key == GLFW_KEY_S)
		{
			direction.y -= 1;
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
			fireball->getTransform()->SetScale(glm::vec2(texture.Width, texture.Height));

			const std::vector textureListFireball = ResourceManager::GetTexturesContaining(dropCallback->paths[i]);
			const auto sprite = fireball->addComponent<AnimatedSpriteRenderer>(textureListFireball, 0.05f);
			sprite->setColor(glm::vec3(1, 1, 1));

			mousePos.x = mousePos.x - texture.Width;
			mousePos.y = mousePos.y - texture.Height;
		}
	}
};

#pragma once
#include "Components/TestGameComponent.h"
#include "Core/SceneManager.h"
#include "Core/Components/Transform.h"
#include "Core/Renderer/ResourceManager.h"
#include "Util/SingletonTemplate.h"
#include "Util/Time.h"
#include "Util/Events/EngineEvents.h"
#include "Core/Components/AnimatedSpriteRenderer.h"
#include "Core/Grid/GridSystem.h"

class TestGameplaySystem : public SingletonTemplate<TestGameplaySystem>
{
public:
	std::list<SpriteRenderer*> sprites;
	
	void TestFunc(OnEngineStart*)
	{
		for (int y = 0; y < 100; y++)
		{
			// Get random position
			float x = rand() % 1920;
			float yy = rand() % 1080;
			
			auto* test = SceneManager::Instance()->createGameObject("Test-1", glm::vec2 { x, yy });
			test->addComponent<TestGameComponent>();
			test->getTransform()->SetScale(glm::vec2(100,100));

			// pick a random texture between these 2
			int textureIndex = rand() % 2;
			
			auto sprite = test->addComponent<SpriteRenderer>();
			sprite->setColor(glm::vec3(1,1,1));
			sprite->texture = ResourceManager::GetTexture(textureIndex == 0 ? "face" : "face2");
			sprites.push_back(sprite);
			
			test->getTransform()->SetRotation(rand() % 360);

			// Get a random rgb color between 0 - 1
			float r = (rand() % 100) / 100.0f;
			float g = (rand() % 100) / 100.0f;
			float b = (rand() % 100) / 100.0f;
			sprite->setColor(glm::vec3(r, g, b));
		}
	}

	void TestFuncLewis(OnEngineStart*) 
	{
		GridSystem::Instance()->init(glm::vec2(96, 48), glm::vec2(100, 100));
		
		auto *test = SceneManager::Instance()->createGameObject("TestBlue-Slime-Idle Idle", glm::vec2{100, 100});
		test->getTransform()->SetScale(glm::vec2(96, 48));

		std::vector textureList = ResourceManager::GetTexturesContaining("Blue-Slime-Idle");

		auto sprite = test->addComponent<AnimatedSpriteRenderer>(textureList, 0.05f);
		sprite->setColor(glm::vec3(1, 1, 1));
		sprites.push_back(sprite);

		auto* testHurt = SceneManager::Instance()->createGameObject("TestBlue-Slime-Idle Hurt", glm::vec2{ 300, 300 });
		testHurt->getTransform()->SetScale(glm::vec2(96, 48));

		std::vector textureListHurt = ResourceManager::GetTexturesContaining("Blue-Slime-Hurt");

		sprite = testHurt->addComponent<AnimatedSpriteRenderer>(textureListHurt, 0.05f);
		sprite->setColor(glm::vec3(1, 1, 1));
		sprites.push_back(sprite);
			

		auto* fireball = SceneManager::Instance()->createGameObject("TestFireball", glm::vec2{ 200, 200 });
		fireball->getTransform()->SetScale(glm::vec2(48, 48));

		std::vector textureListFireball = ResourceManager::GetTexturesContaining("Fireball");

		sprite = fireball->addComponent<AnimatedSpriteRenderer>(textureListFireball, 0.05f);
		sprite->setColor(glm::vec3(1, 1, 1));
		sprites.push_back(sprite);
	}

	void TestFuncUpdate(OnEngineUpdate*)
	{
		// Update all sprites color to be a random color
		for (const auto& sprite : sprites)
		{
			Transform* transform = sprite->owner->getTransform();
			transform->SetPosition(transform->GetPosition() + glm::vec2(100 * Time::getDeltaTime(), 0));
		}
	}

	void TestKeyDown(const OnKeyDown* KeyDownEvent)
	{
		const char* str = glfwGetKeyName(KeyDownEvent->key, KeyDownEvent->scancode);
		if (!str) return;
		std::string strs(str);
		LOG_INFO("Down: " + strs);
	}

	void TestKeyUp(const OnKeyUp* KeyUpEvent)
	{
		const char* str = glfwGetKeyName(KeyUpEvent->key, KeyUpEvent->scancode);
		if (!str) return;
		std::string strs(str);
		LOG_INFO("Up: " + strs);
	}

	void TestKeyRepeat(const OnKeyRepeat* KeyRepeatEvent)
	{
		const char* str = glfwGetKeyName(KeyRepeatEvent->key, KeyRepeatEvent->scancode);
		if (!str) return;
		std::string strs(str);
		LOG_INFO("Repeat: " + strs);
	}

	void TestMouseDown(const OnMouseDown* mouseDownEvent)
	{
		std::string strs(std::to_string(mouseDownEvent->key));
		LOG_INFO("Mouse-Down: " + strs);
	}

	void TestMouseUp(const OnMouseUp* mouseUpEvent)
	{
		std::string strs(std::to_string(mouseUpEvent->key));
		LOG_INFO("Mouse-Up: " + strs);
	}
};

#pragma once
#include "Components/TestGameComponent.h"
#include "Core/SceneManager.h"
#include "Core/Components/Transform.h"
#include "Core/Renderer/ResourceManager.h"
#include "Util/SingletonTemplate.h"
#include "Util/Time.h"
#include "Util/Events/EngineEvents.h"
#include "Components/AnimatedSpriteRenderer.h"

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
			
			auto* test = SceneManager::Instance()->createGameObject(glm::vec2 { x, yy } );
			test->addComponent(new TestGameComponent());
			test->getTransform()->SetScale(glm::vec2(100,100));

			// pick a random texture between these 2
			int textureIndex = rand() % 2;
			
			auto sprite = new SpriteRenderer();
			sprite->color = glm::vec3(1,1,1);
			sprite->texture = ResourceManager::GetTexture(textureIndex == 0 ? "face" : "face2");
			test->addComponent(sprite);
			sprites.push_back(sprite);
			
			test->getTransform()->SetRotation(rand() % 360);

			// Get a random rgb color between 0 - 1
			float r = (rand() % 100) / 100.0f;
			float g = (rand() % 100) / 100.0f;
			float b = (rand() % 100) / 100.0f;
			sprite->color = glm::vec3(r, g, b);
		}
	}

	void TestFuncLewis(OnEngineStart*) 
	{
		auto *test = SceneManager::Instance()->createGameObject(glm::vec2{100, 100});
		test->getTransform()->SetScale(glm::vec2(96, 48));

		std::vector<Texture> textureList =
		{
			ResourceManager::GetTexture("BlueSlime000"),
			ResourceManager::GetTexture("BlueSlime001"),
			ResourceManager::GetTexture("BlueSlime002"),
			ResourceManager::GetTexture("BlueSlime003"),
			ResourceManager::GetTexture("BlueSlime004"),
			ResourceManager::GetTexture("BlueSlime005"),
			ResourceManager::GetTexture("BlueSlime006"),
		};

		auto sprite = new AnimatedSpriteRenderer(textureList, 0.05f);
		sprite->color = glm::vec3(1, 1, 1);
		test->addComponent(sprite);
		sprites.push_back(sprite);

		auto* testHurt = SceneManager::Instance()->createGameObject(glm::vec2{ 300, 300 });
		testHurt->getTransform()->SetScale(glm::vec2(96, 48));

		std::vector<Texture> textureListHurt =
		{
			ResourceManager::GetTexture("BlueSlimeHurt000"),
			ResourceManager::GetTexture("BlueSlimeHurt001"),
			ResourceManager::GetTexture("BlueSlimeHurt002"),
			ResourceManager::GetTexture("BlueSlimeHurt003"),
			ResourceManager::GetTexture("BlueSlimeHurt004"),
			ResourceManager::GetTexture("BlueSlimeHurt005"),
			ResourceManager::GetTexture("BlueSlimeHurt006"),
			ResourceManager::GetTexture("BlueSlimeHurt007"),
			ResourceManager::GetTexture("BlueSlimeHurt008"),
			ResourceManager::GetTexture("BlueSlimeHurt009"),
			ResourceManager::GetTexture("BlueSlimeHurt0010"),

			
		};

		sprite = new AnimatedSpriteRenderer(textureListHurt, 0.05f);
		sprite->color = glm::vec3(1, 1, 1);
		testHurt->addComponent(sprite);
		sprites.push_back(sprite);
			
	}

	void TestFuncUpdate(OnEngineUpdate*)
	{
		// Update all sprites color to be a random color
		for (auto& sprite : sprites)
		{
			float deltaTime = Time::Instance()->getDeltaTime();
			sprite->color = sprite->color + glm::vec3(deltaTime * 0.1, deltaTime * 0.1, deltaTime * 0.1);
			
			if (sprite->color.r > 1.0f)
				sprite->color.r = 0.0f;
			if (sprite->color.g > 1.0f)
				sprite->color.g = 0.0f;
			if (sprite->color.b > 1.0f)
				sprite->color.b = 0.0f;
			
			Transform* transform = sprite->owner->getTransform();
			transform->SetRotation(transform->GetRotation() + Time::getDeltaTime() * 100);
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
};

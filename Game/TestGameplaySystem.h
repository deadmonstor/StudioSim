#pragma once
#include <string>
#include "ScoreSystem.h"
#include "Shop.h"
#include "Components/EnemyTest.h"
#include "Components/FireballComponent.h"
#include "Core/Input.h"
#include "Core/SceneManager.h"
#include "Core/Components/AnimatedSpriteRenderer.h"
#include "Core/Components/TextRenderer.h"
#include "Core/Components/Transform.h"
#include "Core/Components/AI/StateMachine.h"
#include "Core/Grid/GridSystem.h"
#include "Core/Renderer/ResourceManager.h"
#include "Util/SingletonTemplate.h"
#include "Util/Time.h"
#include "Util/Events/EngineEvents.h"
#include "Components/Player/PlayerController.h"
#include "Components/TurnManager.h"
#include "Components/UI/HUD.h"
#include "Tiles/LightTile.h"
#include "Tiles/TestTile.h"
#include "Tiles/TeleportTile.h"

class TestGameplaySystem : public SingletonTemplate<TestGameplaySystem>
{
	StateMachine* sm;
public:
	void CreateFireball(glm::vec2 mousePos)
	{
		mousePos.x = mousePos.x;
		mousePos.y = mousePos.y;
		
		auto* fireball = SceneManager::Instance()->createGameObject("TestFireball", mousePos);
		fireball->getTransform()->setSize(glm::vec2(48, 48));
		fireball->addComponent<FireballComponent>();
		sm = fireball->addComponent<StateMachine>();

		////Crab Anim
		//auto* testPlayerIdle = SceneManager::Instance()->createGameObject("Crab", glm::vec2{ 1600, 2600 });
		//testPlayerIdle->getTransform()->setSize(glm::vec2(256, 256));

		//const std::vector textureListPlayer = ResourceManager::GetTexturesContaining("crab");
		//auto sprite = testPlayerIdle->addComponent<AnimatedSpriteRenderer>(textureListPlayer, 0.075f);
		//sprite->setColor(glm::vec3(1, 1, 1));
		//sprite->setLit(false);
	}
	
	void TestMouseDown(const OnMouseDown* mouseDownEvent)
	{
		const glm::vec2 mousePos = Input::getMousePosition();
		if (sm != nullptr)
		{
			std::type_index type = typeid(OnMouseDown);
			Griddy::Events::invoke<BehaviourEvent>(sm, new OnMouseDown(mouseDownEvent->key, mouseDownEvent->action), type);
		}
		if (mouseDownEvent->key == GLFW_MOUSE_BUTTON_3)
		{
			CreateFireball(mousePos);
		}
	}
};

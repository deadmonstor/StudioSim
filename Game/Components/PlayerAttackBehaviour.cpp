#include "PlayerAttackBehaviour.h"
#include "PlayerMovementBehaviour.h"
#include "Core/Grid/GridSystem.h"
#include "DestroyAfterAnimation.h"
#include "Core/Components/Transform.h"

PlayerAttackBehaviour::PlayerAttackBehaviour(bool isInFSMParam)
{
	isInFSM = isInFSMParam;
	map = CreateFunctionMap();
	
}

void PlayerAttackBehaviour::Act()
{
	if(canAttack)
	{
		currentPlayerPos = (PlayerController::Instance()->playerPTR->getTransform()->getPosition()) / GridSystem::Instance()->getTileSize();
		TileHolder* curTileHolder = GridSystem::Instance()->getTileHolder(0, currentPlayerPos + attackDir);
		glm::fvec2 tileSize = GridSystem::Instance()->getTileSize();

		if (curTileHolder->tile != nullptr && !curTileHolder->isWall)
		{
			switch (weaponClassEquipped)
			{
				case Dagger:
				{
					GameObject* slash = SceneManager::Instance()->createGameObject("Slash", (tileSize * (currentPlayerPos + attackDir)));
					slash->getTransform()->setSize(glm::vec2(48, 48));
					AnimatedSpriteRenderer* slashSprite = slash->addComponent<AnimatedSpriteRenderer>(textureListRST, 0.05f);
					slashSprite->setPivot(Pivot::Center);
					slash->addComponent<DestroyAfterAnimation>();
					break;
				}

				case Sword:
				{
					if (attackDir == glm::fvec2{ 0,1 } || attackDir == glm::fvec2{ 0,-1 })
					{
						std::vector<glm::fvec2> attackPosSword = { (tileSize * (currentPlayerPos + attackDir)),
							(tileSize * (currentPlayerPos + attackDir + glm::fvec2(-1, 0))) ,
							(tileSize * (currentPlayerPos + attackDir + glm::fvec2(1, 0))) };

						attackPositions.assign_range(attackPosSword);
						for (glm::fvec2 attackPos : attackPositions)
						{
							GameObject* slash = SceneManager::Instance()->createGameObject("Slash", attackPos);
							slash->getTransform()->setSize(glm::vec2(48, 48));
							AnimatedSpriteRenderer* slashSprite = slash->addComponent<AnimatedSpriteRenderer>(textureListRST, 0.05f);
							slashSprite->setPivot(Pivot::Center);
							slash->addComponent<DestroyAfterAnimation>();
						}
					}
					else
					{
						std::vector<glm::fvec2> attackPosSword = { (tileSize * (currentPlayerPos + attackDir)),
							(tileSize * (currentPlayerPos + attackDir + glm::fvec2(0, 1))) ,
							(tileSize * (currentPlayerPos + attackDir + glm::fvec2(0, -1))) };

						attackPositions.assign_range(attackPosSword);
						for (glm::fvec2 attackPos : attackPositions)
						{
							GameObject* slash = SceneManager::Instance()->createGameObject("Slash", attackPos);
							slash->getTransform()->setSize(glm::vec2(48, 48));
							AnimatedSpriteRenderer* slashSprite = slash->addComponent<AnimatedSpriteRenderer>(textureListRST, 0.05f);
							slashSprite->setPivot(Pivot::Center);
							slash->addComponent<DestroyAfterAnimation>();
						}
					}
					break;
				}
				case Axe:
				{
					std::vector<glm::fvec2> attackPosAxe = { (tileSize * (currentPlayerPos + attackDir)),
						(tileSize * (currentPlayerPos + attackDir + attackDir)) };

					attackPositions.assign_range(attackPosAxe);
					for (glm::fvec2 attackPos : attackPositions)
					{
						GameObject* slash = SceneManager::Instance()->createGameObject("Slash", attackPos);
						slash->getTransform()->setSize(glm::vec2(48, 48));
						AnimatedSpriteRenderer* slashSprite = slash->addComponent<AnimatedSpriteRenderer>(textureListRST, 0.05f);
						slashSprite->setPivot(Pivot::Center);
						slash->addComponent<DestroyAfterAnimation>();
					}
					break;
				}

				case Hammer:
				{
					glm::fvec2 firstTileinAttackDir = (tileSize * (currentPlayerPos + attackDir));
					glm::fvec2 secondTileinAttackDir = (tileSize * (currentPlayerPos + attackDir + attackDir));
					if (attackDir == glm::fvec2{ 0,1 } || attackDir == glm::fvec2{ 0,-1 })
					{
						std::vector<glm::fvec2> attackPosHammer = { firstTileinAttackDir, firstTileinAttackDir + (tileSize * glm::fvec2(1, 0)),
						firstTileinAttackDir + (tileSize * glm::fvec2(-1, 0)), secondTileinAttackDir, secondTileinAttackDir + (tileSize * glm::fvec2(1, 0)),
						secondTileinAttackDir + (tileSize * glm::fvec2(-1, 0)) };

						attackPositions.assign_range(attackPosHammer);

						for (glm::fvec2 attackPos : attackPositions)
						{
							GameObject* slash = SceneManager::Instance()->createGameObject("Slash", attackPos);
							slash->getTransform()->setSize(glm::vec2(48, 48));
							AnimatedSpriteRenderer* slashSprite = slash->addComponent<AnimatedSpriteRenderer>(textureListRST, 0.05f);
							slashSprite->setPivot(Pivot::Center);
							slash->addComponent<DestroyAfterAnimation>();
						}
					}
					else
					{
						std::vector<glm::fvec2> attackPosHammer = { firstTileinAttackDir, firstTileinAttackDir + (tileSize * glm::fvec2(0, 1)),
						firstTileinAttackDir + (tileSize * glm::fvec2(0, -1)), secondTileinAttackDir, secondTileinAttackDir + (tileSize * glm::fvec2(0, 1)),
						secondTileinAttackDir + (tileSize * glm::fvec2(0, -1)) };

						attackPositions.assign_range(attackPosHammer);

						for (glm::fvec2 attackPos : attackPositions)
						{
							GameObject* slash = SceneManager::Instance()->createGameObject("Slash", attackPos);
							slash->getTransform()->setSize(glm::vec2(48, 48));
							AnimatedSpriteRenderer* slashSprite = slash->addComponent<AnimatedSpriteRenderer>(textureListRST, 0.05f);
							slashSprite->setPivot(Pivot::Center);
							slash->addComponent<DestroyAfterAnimation>();
						}
					}
					break;
				}

			}

			attackPositions.clear();
		}
		canAttack = false;
	}
	
}

void PlayerAttackBehaviour::onKeyDownResponse(Griddy::Event* event)
{
	OnKeyDown* eventCasted = static_cast<OnKeyDown*>(event);

	if (eventCasted->key == GLFW_KEY_Q)
	{
		Griddy::Events::invoke<StateTransition>((StateMachine*)PlayerController::Instance()->playerFSM, new PlayerMovementBehaviour(true));
		return;
	}

	if (eventCasted->key == GLFW_KEY_E)
	{
		weaponClassEquipped = Dagger;
	}
	else if (eventCasted->key == GLFW_KEY_R)
	{
		weaponClassEquipped = Sword;
	}
	else if (eventCasted->key == GLFW_KEY_T)
	{
		weaponClassEquipped = Hammer;
	}
	else if (eventCasted->key == GLFW_KEY_Y)
	{
		weaponClassEquipped = Axe;
	}

	if (eventCasted->key == GLFW_KEY_W)
	{
		attackDir.y += 1;
		Act();
	}
	else if (eventCasted->key == GLFW_KEY_S)
	{
		attackDir.y -= 1;
		Act();
	}
	else if (eventCasted->key == GLFW_KEY_A)
	{
		attackDir.x -= 1;
		Act();
	}
	else if (eventCasted->key == GLFW_KEY_D)
	{
		attackDir.x += 1;
		Act();
	}

	attackDir = glm::fvec2(0, 0);
}

void PlayerAttackBehaviour::onKeyUpResponse(Griddy::Event* event)
{
	/*OnKeyUp* eventCasted = static_cast<OnKeyUp*>(event);

	if (eventCasted->key == GLFW_KEY_W)
	{
		attackDir.y -= 1;
	}
	else if (eventCasted->key == GLFW_KEY_S)
	{
		attackDir.y += 1;
	}
	else if (eventCasted->key == GLFW_KEY_A)
	{
		attackDir.x += 1;
	}
	else if (eventCasted->key == GLFW_KEY_D)
	{
		attackDir.x -= 1;
	}*/

	canAttack = true;
}

FunctionMap PlayerAttackBehaviour::CreateFunctionMap()
{
	FunctionMap map = {};
	map[typeid(OnKeyDown)] =
		[](Behaviour* pointer, Griddy::Event* event)
	{
		dynamic_cast<PlayerAttackBehaviour*>(pointer)->onKeyDownResponse(event);
	};
	map[typeid(OnKeyUp)] =
		[](Behaviour* pointer, Griddy::Event* event)
	{
		dynamic_cast<PlayerAttackBehaviour*>(pointer)->onKeyUpResponse(event);
	};

	return map;
}

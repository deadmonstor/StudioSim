#include "PlayerAttackBehaviour.h"
#include "PlayerMovementBehaviour.h"
#include "Core/Grid/GridSystem.h"
#include "Components/DestroyAfterAnimation.h"

PlayerAttackBehaviour::PlayerAttackBehaviour(bool isInFSMParam)
{
	isInFSM = isInFSMParam;
	map = CreateFunctionMap();
	
}

void PlayerAttackBehaviour::Act()
{
	
	currentPlayerPos = (PlayerController::Instance()->playerPTR->getTransform()->getPosition()) / GridSystem::Instance()->getTileSize();
	TileHolder* curTileHolder = GridSystem::Instance()->getTileHolder(0, currentPlayerPos + moveDir);
	glm::fvec2 tileSize = GridSystem::Instance()->getTileSize();
	
	if (curTileHolder->tile != nullptr && !curTileHolder->isWall)
	{
		switch (weaponClassEquipped)
		{
		case Dagger:
			GameObject* slash = SceneManager::Instance()->createGameObject("Slash", (tileSize * (currentPlayerPos + moveDir)));
			slash->getTransform()->setSize(glm::vec2(48, 48));
			AnimatedSpriteRenderer* slashSprite = slash->addComponent<AnimatedSpriteRenderer>(textureListRST, 0.05f);
			slash->addComponent<DestroyAfterAnimation>();

			break;
			/*case Sword:
				break;
			case Axe:
				break;
			case Hammer:
				break;*/
		}
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
		moveDir.y += 1;
		Act();
	}
	else if (eventCasted->key == GLFW_KEY_S)
	{
		moveDir.y -= 1;
		Act();
	}
	else if (eventCasted->key == GLFW_KEY_A)
	{
		moveDir.x -= 1;
		Act();
	}
	else if (eventCasted->key == GLFW_KEY_D)
	{
		moveDir.x += 1;
		Act();
	}
}

void PlayerAttackBehaviour::onKeyUpResponse(Griddy::Event* event)
{
	OnKeyUp* eventCasted = static_cast<OnKeyUp*>(event);

	if (eventCasted->key == GLFW_KEY_W)
	{
		moveDir.y -= 1;
	}
	else if (eventCasted->key == GLFW_KEY_S)
	{
		moveDir.y += 1;
	}
	else if (eventCasted->key == GLFW_KEY_A)
	{
		moveDir.x += 1;
	}
	else if (eventCasted->key == GLFW_KEY_D)
	{
		moveDir.x -= 1;
	}
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

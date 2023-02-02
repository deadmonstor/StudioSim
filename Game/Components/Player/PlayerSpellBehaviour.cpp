#include "PlayerSpellBehaviour.h"
#include "PlayerMovementBehaviour.h"
#include "../TurnManager.h"

PlayerSpellBehaviour::PlayerSpellBehaviour()
{
	isInFSM = false;
	map = CreateFunctionMap();
}

PlayerSpellBehaviour::PlayerSpellBehaviour(bool isInFSMParam)
{
	isInFSM = isInFSMParam;
	map = CreateFunctionMap();
}

void PlayerSpellBehaviour::Act()
{
	canThrowSpell = false;
	if (TurnManager::Instance()->isCurrentTurnObject(PlayerController::Instance()->playerPTR) && !willFlashOnce)
		TurnManager::Instance()->endTurn();
}

void PlayerSpellBehaviour::onKeyDownResponse(Griddy::Event* event)
{
	OnKeyDown* eventCasted = static_cast<OnKeyDown*>(event);

	if (eventCasted->key == GLFW_KEY_E)
	{
		Griddy::Events::invoke<StateTransition>((StateMachine*)PlayerController::Instance()->playerFSM, new PlayerMovementBehaviour(true));
	}

	if (eventCasted->key == GLFW_KEY_W)
	{
		attackDir.y = 1;
	}
	else if (eventCasted->key == GLFW_KEY_S)
	{
		attackDir.y = -1;
	}
	else if (eventCasted->key == GLFW_KEY_A)
	{
		attackDir.x = -1;
	}
	else if (eventCasted->key == GLFW_KEY_D)
	{
		attackDir.x = 1;
	}

	attackDir = glm::fvec2(0, 0);

	if (canThrowSpell && (eventCasted->key == GLFW_KEY_W || eventCasted->key == GLFW_KEY_S ||
		eventCasted->key == GLFW_KEY_A || eventCasted->key == GLFW_KEY_D))
	{
		if (TurnManager::gNoclipMode || TurnManager::Instance()->isCurrentTurnObject(PlayerController::Instance()->playerPTR))
		{
			Act();
		}
	}
}

void PlayerSpellBehaviour::onKeyUpResponse(Griddy::Event*)
{
	canThrowSpell = true;
}

FunctionMap PlayerSpellBehaviour::CreateFunctionMap()
{
	FunctionMap map = {};
	map[typeid(OnKeyDown)] =
		[](Behaviour* pointer, Griddy::Event* event)
	{
		dynamic_cast<PlayerSpellBehaviour*>(pointer)->onKeyDownResponse(event);
	};
	map[typeid(OnKeyUp)] =
		[](Behaviour* pointer, Griddy::Event* event)
	{
		dynamic_cast<PlayerSpellBehaviour*>(pointer)->onKeyUpResponse(event);
	};

	return map;
}
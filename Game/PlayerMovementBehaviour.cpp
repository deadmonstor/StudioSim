#include "PlayerMovementBehaviour.h"
#include <Util/Events/EngineEvents.h>

void PlayerMovementBehaviour::Act()
{
	//move player
	glm::vec2 currentPosition = PlayerController::Instance()->playerPTR->getTransform()->getPosition();
	PlayerController::Instance()->playerPTR->getTransform()->setPosition(currentPosition + moveDir * glm::vec2{10, 10});

}

void PlayerMovementBehaviour::onKeyDownResponse(const Griddy::Event* event)
{
	OnKeyDown* eventCasted = (OnKeyDown*)event;

	if (eventCasted->key == GLFW_KEY_W)
	{
		moveDir.y += 1;
	}
	else if (eventCasted->key == GLFW_KEY_S)
	{
		moveDir.y -= 1;
	}
	else if (eventCasted->key == GLFW_KEY_A)
	{
		moveDir.x -= 1;
	}
	else if (eventCasted->key == GLFW_KEY_D)
	{
		moveDir.x += 1;
	}

	//if tile is moveable
	Act();
}

void PlayerMovementBehaviour::onKeyUpResponse(const Griddy::Event* event)
{
	OnKeyUp* eventCasted = (OnKeyUp*)event;

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

FunctionMap PlayerMovementBehaviour::CreateFunctionMap()
{
	FunctionMap map = {};
	map[typeid(OnKeyDown)] =
		[](Behaviour* pointer, const Griddy::Event* event)
	{
		((PlayerMovementBehaviour*)pointer)->onKeyDownResponse(event);
	};
	map[typeid(OnKeyUp)] =
		[](Behaviour* pointer, const Griddy::Event* event)
	{
		((PlayerMovementBehaviour*)pointer)->onKeyUpResponse(event);
	};

	return map;
	
}

//void PlayerMovementBehaviour::EventResponse(const BehaviourEvent* event)
//{
//	//Read input and find direction
//	//check tiles available to move
//	//call act at the end
//	OnKeyDown* eventCasted = (OnKeyDown*)event;
//
	/*if (eventCasted->key == GLFW_KEY_W)
	{
		moveDir.y += 1;
	}
	else if (eventCasted->key == GLFW_KEY_S)
	{
		moveDir.y -= 1;
	}
	else if (eventCasted->key == GLFW_KEY_A)
	{
		moveDir.x -= 1;
	}
	else if (eventCasted->key == GLFW_KEY_D)
	{
		moveDir.x += 1;
	}*/
//}

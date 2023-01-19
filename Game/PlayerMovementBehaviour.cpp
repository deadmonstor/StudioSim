#include "PlayerMovementBehaviour.h"
#include <Util/Events/EngineEvents.h>

void PlayerMovementBehaviour::Act()
{
	//move player
}

void PlayerMovementBehaviour::onKeyDownResponse(Griddy::Event* event)
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

	Act();
}

FunctionMap PlayerMovementBehaviour::CreateFunctionMap()
{
	FunctionMap map = {};
	map[typeid(OnKeyDown)] =
		[](Behaviour* pointer, Griddy::Event* event)
	{
		((PlayerMovementBehaviour*)pointer)->onKeyDownResponse(event);
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

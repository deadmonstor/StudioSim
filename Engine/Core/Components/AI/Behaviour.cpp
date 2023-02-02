#include "Behaviour.h"



Behaviour::Behaviour(bool isInFSMParam)
{
	isInFSM = isInFSMParam;
	map = CreateFunctionMap();
}

void Behaviour::EventResponse(BehaviourEvent* event)
{
	
	//find change in behaviour, or invoke an event with state transition.
	//This would be handled in the mapped functions.
	if (event->targetBehaviour == this)
	{

		if (map.contains(event->type))
		{
			map[event->type](this, event->readEvent);
		}
		else
		{
			LOG_ERROR("Map doesn't have type");
		}
	}

}

void Behaviour::start()
{
	if (!isInFSM)
	{
		if (eventResponseID == -1)
			eventResponseID = Griddy::Events::subscribe(this, &Behaviour::EventResponse);
	}




	initialized = true;

	Component::start();
}

void Behaviour::destroy()
{
	if (eventResponseID != -1)
	{
		Griddy::Events::unsubscribe(this, &Behaviour::EventResponse, eventResponseID);
		eventResponseID = -1;
	}
	initialized = false;
	
	Component::destroy();
}

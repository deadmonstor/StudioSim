#include "Behaviour.h"

void Behaviour::EventResponse(BehaviourEvent* event)
{
	
	//find change in behaviour, or invoke an event with state transition.
	//This would be handled in the mapped functions.

	if (map.contains(event->type))
	{
		map[event->type](this, event->readEvent);
	}
	else 
	{
		LOG_ERROR("Map doesn't have type");
	}
}

void Behaviour::start()
{
	if (eventResponseID == -1)
		eventResponseID = Griddy::Events::subscribe(this, &Behaviour::EventResponse);
	map = CreateFunctionMap();


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
	
	Component::destroy();
}

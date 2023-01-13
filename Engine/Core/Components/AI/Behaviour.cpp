#include "Behaviour.h"

void Behaviour::EventResponse(const BehaviourEvent* event)
{
	if (event->targetBehaviour == this)
	{
		LOG_INFO("Behaviour receives event");
		//find change in behaviour, or invoke an event with state transition
		//continue here....
	}
}

void Behaviour::start()
{
	if (eventResponseID == -1)
		eventResponseID = Griddy::Events::subscribe(this, &Behaviour::EventResponse);
	
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

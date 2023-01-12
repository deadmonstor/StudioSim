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
	Griddy::Events::subscribe(this, &Behaviour::EventResponse);
	initialized = true;
}

#pragma once
#include "Core/Component.h"

#include "Util/Events/Events.h"
#include "Util/Events/AIEvents.h"

//Interface defining AI behaviours. Derive this interface into unique game behaviours.
class Behaviour : public Component
{
//Public Methods
public:

	//Function defining a single-shot behaviour
	virtual void Act();



	void start() override;
	void update() override {}
	void lateUpdate() override {}

	void EventResponse(const Griddy::Event readEvent);

	virtual void CleanUp();
};

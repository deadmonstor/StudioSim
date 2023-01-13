#pragma once
#include "Core/Component.h"

#include "Util/Events/Events.h"
#include "Util/Events/AIEvents.h"

#include <map>

//Interface defining AI behaviours. Derive this interface into unique game behaviours.
class Behaviour : public Component
{
protected:
	bool initialized = false;
	int8_t eventResponseID = -1;
	//Public Methods
public:
	/*space for expansion : insert Entry() and Exit() functions which can
	 perform actions */

	//Function defining a single-shot behaviour
	virtual void Act() {}
	virtual void EventResponse(const BehaviourEvent* event);


	void start() override;
	void update() override {}
	void lateUpdate() override {}
	void destroy() override;

	bool GetInitValue() { return initialized; }
};

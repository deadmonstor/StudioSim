#pragma once
#include "Core/Component.h"

#include "Core/GameObject.h"
#include "Util/Events/Events.h"
#include "Util/Events/AIEvents.h"

//Interface defining AI behaviours. Derive this interface into unique game behaviours.
class Behaviour final : public Component
{
//Properties
protected:
	bool initialised;
	bool entered;
//Public Methods
public:
	Behaviour();
	~Behaviour() override;

	//Function played when the behaviour starts
	virtual void Entry();
	//Function played when the behaviour exits
	virtual void Exit();

	//Function defining a single-shot behaviour
	virtual void Act();



	void start() override;
	void update() override {}
	void lateUpdate() override {}

	//Extracts transition data to find the event to transition to (might change this to enum?)
	Behaviour* FindTransition(const FSMTransition transitionEvent);

	virtual void CleanUp();
};

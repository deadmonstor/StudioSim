#pragma once

#include "Core/Component.h"
#include "Core/Components/AI/Behaviour.h"

#include "Util/Events/Events.h"
#include "Util/Events/AIEvents.h"

#include <vector>

//Class interface used for Behaviour Selection based on FSMTransition Events. Derive this class into unique AI state machines for the games.
class StateMachine final : public Component
{
// Properties
protected:
	bool initialised;

	// List of available behaviours. Can be fed in from outside system, or instantiated in constructor overloads.
	std::vector<Behaviour*> behaviours;

	//The base state that the state machine can return into.
	Behaviour *baseState;
	Behaviour *currentState;

	//Public Methods
public:
	//Default Constructor
	StateMachine();

	//Destructor
	~StateMachine() override;

	//Returns the behaviours list.
	virtual std::vector<Behaviour*> GetBehaviours() { return behaviours; }

	//Adds a new behaviour to the behaviours list.
	virtual void AddBehaviour(Behaviour* behaviourParam);
	//Removes a behaviour from the Behaviours list.
	virtual void RemoveBehaviour(Behaviour* behaviourParam);

	void start() override;
	void update() override;
	void lateUpdate() override;

	//performs Act() on the current state.
	virtual void ActBehaviour();

	//Exits current state, and tells update to wait till its ready for the change.
	virtual void ChangeState(Behaviour *behaviourParam);

	//Sets the behaviour to the state machine's base state.
	virtual void ResetState();

	//Checks the transition against the current state.
	virtual void OnTransitionReceived(const FSMTransition transitionEvent);

protected:
	void CleanUp();

};

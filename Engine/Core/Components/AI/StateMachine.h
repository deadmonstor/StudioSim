#pragma once
#include "Core/Components/AI/Behaviour.h"

//Class interface used for Behaviour Selection based on FSMTransition Events. Derive this class into unique AI state machines for the games.
class StateMachine : public Behaviour
{
// Properties
protected:
	int8_t onTransitionReceivedID = -1;
	//The base state that the state machine can return into.
	Behaviour* baseState = nullptr;
	Behaviour* currentState = nullptr;
	int eventResponseID = -1;
	int onTransitionReceivedID = -1;

//Public Methods
public:

	void destroy() override;
	void start() override;
	void update() override;
	void lateUpdate() override;

	//performs Act() on the current state.
	void Act() override;

	//Exits current state, and tells update to wait till its ready for the change.
	virtual void ChangeState(Behaviour* behaviourParam);

	//Sets the behaviour to the state machine's base state.
	virtual void ResetToBase();

protected:
	//Sends an event to be evaluated by the current behaviour
	void EventResponse(BehaviourEvent* event) override;

	//Receives an event with a new state to transition into
	virtual void OnTransitionReceived(const StateTransition* event);

	void CleanUp();
};

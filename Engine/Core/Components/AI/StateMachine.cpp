#include "StateMachine.h"


void StateMachine::destroy()
{
	CleanUp();
}

void StateMachine::start()
{ 
	Griddy::Events::subscribe(this, &StateMachine::EventResponse);
	Griddy::Events::subscribe(this, &StateMachine::OnTransitionReceived);
	baseState = new Behaviour();
	currentState = baseState;
	if (currentState->GetInitValue() == false)
	{
		currentState->start();
	}
}

void StateMachine::update() 
{ 
	currentState->update();
}

void StateMachine::lateUpdate() 
{
	currentState->lateUpdate();
}

//performs Act() on the current behaviour.
void StateMachine::Act() 
{
	currentState->Act(); 
}

//Exits current state, and tells update to wait till its ready for the change.
void StateMachine::ChangeState(Behaviour* behaviourParam) 
{ 
	currentState->destroy();
	delete currentState;
	currentState = behaviourParam;
	if (currentState->GetInitValue() == false)
	{
		currentState->start();
	}
}

//Sets the behaviour to the state machine's base behaviour.
void StateMachine::ResetToBase() 
{ 
	ChangeState(baseState); 
}

//Sends the event to read by the current state
void StateMachine::EventResponse(const BehaviourEvent* event)
{
	if (event->targetBehaviour == this) {
		LOG_INFO("State Machine receives event");
		Griddy::Events::invoke<BehaviourEvent>(currentState, event);
	}
	
}

//Checks the transition against the current state.
void StateMachine::OnTransitionReceived(const StateTransition* event)
{
	if (event->targetStateMachine == this) 
	{
		ChangeState(event->newBehaviour);
	}
}

void StateMachine::CleanUp()
{
	if (baseState == currentState)
	{
		baseState->destroy();
		delete baseState;
	}
	else {
		baseState->destroy();
		delete baseState;
		currentState->destroy();
		delete currentState;
	}

}

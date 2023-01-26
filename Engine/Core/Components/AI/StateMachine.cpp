#include "StateMachine.h"


void StateMachine::destroy()
{
	if (eventResponseID != -1)
	{
		Griddy::Events::unsubscribe(this, &StateMachine::EventResponse, eventResponseID);

		eventResponseID = -1;
	}
	
	if (onTransitionReceivedID != -1)
	{
		Griddy::Events::unsubscribe(this, &StateMachine::OnTransitionReceived, onTransitionReceivedID);
		onTransitionReceivedID = -1;
	}
	
	CleanUp();

	Component::destroy();
}

void StateMachine::start()
{
	if (eventResponseID == -1) {
		eventResponseID = Griddy::Events::subscribe(this, &StateMachine::EventResponse);
	}
	
	if (onTransitionReceivedID == -1)
		onTransitionReceivedID = Griddy::Events::subscribe(this, &StateMachine::OnTransitionReceived);
	
	baseState = new Behaviour(true);
	currentState = baseState;

	if (currentState->GetInitValue() == false)
	{
		currentState->start();
	}
	Component::start();
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
	currentState = nullptr;
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
void StateMachine::EventResponse(BehaviourEvent* event)
{
	if (event->targetBehaviour == this)
	{
		event->targetBehaviour = currentState;
		currentState->EventResponse(event);
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
		baseState = nullptr;
		currentState = nullptr;
	}
	else
	{
		baseState->destroy();
		delete baseState;
		baseState = nullptr;
		currentState->destroy();
		delete currentState;
		currentState = nullptr;
	}

}

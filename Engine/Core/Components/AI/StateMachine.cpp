#include "StateMachine.h"


void StateMachine::destroy()
{
	CleanUp();
	Component::destroy();
}

void StateMachine::start()
{ 

}

void StateMachine::update() 
{ 

}

void StateMachine::lateUpdate() 
{

}

//performs Act() on the current behaviour.
void StateMachine::Act() 
{
	currentState->Act(); 
}

//Exits current state, and tells update to wait till its ready for the change.
void StateMachine::ChangeState(Behaviour* behaviourParam) 
{ 
	//continue here....
}

//Sets the behaviour to the state machine's base behaviour.
void StateMachine::ResetToBase() 
{ 
	ChangeState(baseState); 
}

//Sends the event to read by the current state
void StateMachine::EventResponse(BehaviourEvent* readEvent)
{
	currentState->EventResponse(readEvent);
}

//Checks the transition against the current state.
void StateMachine::OnTransitionReceived(const FSMTransition* transitionEvent) 
{
	//continue here....
}

void StateMachine::CleanUp()
{
	baseState->destroy();
	delete baseState;
	currentState->destroy();
	delete currentState;
}

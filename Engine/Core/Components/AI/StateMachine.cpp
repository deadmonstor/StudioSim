#include "StateMachine.h"

//Default Constructor
StateMachine::StateMachine() 
{ 
	initialised = false; 
	baseState = nullptr;
	currentState = nullptr;
}

//Destructor
StateMachine::~StateMachine() 
{
	initialised = false;
	baseState = nullptr;
	currentState = nullptr;
	CleanUp();

}

//Adds a new behaviour to the behaviours list.
void StateMachine::AddBehaviour(Behaviour *behaviourParam) 
{ 
	behaviours.push_back(behaviourParam); 
}

//Removes a behaviour from the Behaviours list.
void StateMachine::RemoveBehaviour(Behaviour *behaviourParam) 
{
	auto it = std::find(behaviours.begin(), behaviours.end(), behaviourParam);
	if (it != behaviours.end())
	{
		behaviours.erase(it);
	}
}

void StateMachine::start() 
{ 
	if (initialised) 
	{
		baseState = behaviours.at(0);
		currentState = baseState;
	}
	baseState->start();
}

void StateMachine::update() 
{ 
	if (initialised) 
	{
		currentState->update();
	}
}

void StateMachine::lateUpdate() 
{
	if (initialised)
	{
		currentState->lateUpdate();
	}
}

//performs Act() on the current behaviour.
void StateMachine::ActBehaviour() 
{
	currentState->Act(); 
}

//Exits current state, and tells update to wait till its ready for the change.
void StateMachine::ChangeState(Behaviour *behaviourParam) 
{ 
	currentState->Exit(); 
	//continue here....
}

//Sets the behaviour to the state machine's base behaviour.
void StateMachine::ResetState() 
{ 
	ChangeState(baseState); 
}

//Checks the transition against the current state.
void StateMachine::OnTransitionReceived(const FSMTransition transitionEvent) 
{
	//continue here....
}

void StateMachine::CleanUp() 
{
	// garbage collection. Delete behaviour pointers.
	for (Behaviour *i : behaviours)
	{
		i->CleanUp();
		delete i;
	}
	behaviours.clear();
}

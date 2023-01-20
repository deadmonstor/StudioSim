#pragma once
#include "FunctionHandler.h"

#include <string>

class StateMachine;
class Behaviour;

//targets a particular behaviour and sends an event to read
class BehaviourEvent : public Griddy::Event
{
public:
	explicit BehaviourEvent(Behaviour* targetBehaviourParam, Griddy::Event* readEventParam, std::type_index typeParam)
		: targetBehaviour(targetBehaviourParam), readEvent(readEventParam), type(typeParam) { }
	Griddy::Event* readEvent;
	std::type_index type;
	Behaviour* targetBehaviour;
};

//targets a particular state machine and tells it to transition to the parametered behaviour
class StateTransition : public Griddy::Event
{
public:
	explicit StateTransition(StateMachine* targetStateMachineParam, Behaviour* newBehaviourParam)
		: targetStateMachine(targetStateMachineParam), newBehaviour(newBehaviourParam) {}
	Behaviour* newBehaviour;
	StateMachine* targetStateMachine;
};
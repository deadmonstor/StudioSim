#pragma once
#include "FunctionHandler.h"

#include <string>

class StateMachine;
class Behaviour;

//targets a particular behaviour and sends an event to read
class BehaviourEvent : public Griddy::Event
{
public:
	explicit BehaviourEvent(Behaviour* targetBehaviourParam, Griddy::Event* readEventParam)
		: targetBehaviour(targetBehaviourParam), readEvent(readEventParam) {}
	Griddy::Event* readEvent;
	Behaviour* targetBehaviour;
};

//targets a particular state machine and tells it to transition to the parametered behaviour
class FSMTransition : public Griddy::Event
{
public:
	explicit FSMTransition(StateMachine* targetStateMachineParam, Behaviour newBehaviourParam)
		: targetStateMachine(targetStateMachineParam), newBehaviour(newBehaviourParam) {}
	Behaviour newBehaviour;
	StateMachine* targetStateMachine;
};
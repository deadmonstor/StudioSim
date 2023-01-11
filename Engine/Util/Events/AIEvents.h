#pragma once
#include "FunctionHandler.h"

#include <string>

class StateMachine;
class Behaviour;

//unsure about this. Is this the correct structure to make a specific state machine listen to this event?
class FSMTransition : public Griddy::Event
{
public:
	FSMTransition() { stateMachine = nullptr; }
	explicit FSMTransition(StateMachine *stateMachine) : stateMachine(stateMachine) {}
	StateMachine *stateMachine;
};

//continue development here.....
#include "BossStateMachine.h"

void BossStateMachine::start()
{
	StateMachine::start();
	baseState = new BossIdleBehaviour(this);
	currentState = baseState;
	currentState->start();
}

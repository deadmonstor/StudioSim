#include "BossStateMachine.h"

void BossStateMachine::start()
{
	StateMachine::start();
	baseState = new BossIdleBehaviour(this, spawnerPositions);
	currentState = baseState;
	currentState->start();
}

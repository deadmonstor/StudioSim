#include "BossStateMachine.h"

void BossStateMachine::start()
{
	StateMachine::start();
	baseState = new BossIdleBehaviour(this, myPos, spawnerPositions);
	currentState = baseState;
	currentState->start();
}

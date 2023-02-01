#include "NormalEnemyFSM.h"

void NormalEnemyFSM::start()
{
	StateMachine::start();
	baseState = new EnemyIdleBehaviour(this);
	currentState = baseState;
	currentState->start();
}

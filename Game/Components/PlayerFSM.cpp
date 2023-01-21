#include "PlayerFSM.h"

void PlayerFSM::start()
{
	StateMachine::start();
	baseState = new PlayerMovementBehaviour(true);
	currentState = baseState;
	currentState->start();
}

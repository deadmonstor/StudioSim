#include "PlayerFSM.h"

void PlayerFSM::start()
{
	StateMachine::start();
	baseState = new PlayerMovementBehaviour();
	currentState = baseState;
}

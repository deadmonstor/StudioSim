#include "BossStateMachine.h"
#include "Core/Grid/GridSystem.h"

void BossStateMachine::start()
{
	StateMachine::start();
	baseState = new BossIdleBehaviour(this, myPos, spawnerPositions);
	currentState = baseState;
	currentState->start();
}

void BossStateMachine::destroy()
{
	GridSystem::Instance()->resetSatOnTile(0, myPos);
	GridSystem::Instance()->resetSatOnTile(0, myPos + glm::vec2(1, 0));
	Griddy::Events::invoke<BossDeathEvent>();
	StateMachine::destroy();
}

#include "ReaperStateMachine.h"
#include "Core/Grid/GridSystem.h"

void ReaperStateMachine::start()
{
	StateMachine::start();
	baseState = new ReaperIdleBehaviour(this, myPos, spawnerPositions);
	currentState = baseState;
	currentState->start();
}

void ReaperStateMachine::destroy()
{
	GridSystem::Instance()->resetSatOnTile(0, myPos);
	GridSystem::Instance()->resetSatOnTile(0, myPos + glm::vec2(0, 1));
	Griddy::Events::invoke<BossDeathEvent>();
	StateMachine::destroy();
}

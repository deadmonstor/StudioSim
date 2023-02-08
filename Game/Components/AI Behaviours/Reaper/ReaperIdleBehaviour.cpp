#include "ReaperIdleBehaviour.h"
#include "Core/Grid/GridSystem.h"
#include "Core/Components\Transform.h"
#include "Core\Components\AI\StateMachine.h"
#include "ReaperCombatBehaviour.h"

#include "../../TurnManager.h"


ReaperIdleBehaviour::ReaperIdleBehaviour(StateMachine* parentFSMArg, glm::vec2 myPosArg, std::vector<glm::vec2> spawnerPositionsArg)
{
	myPos = myPosArg;
	isInFSM = true;
	parentFSM = parentFSMArg;
	spawnerPositions = spawnerPositionsArg;
}

void ReaperIdleBehaviour::Act()
{
	if (shouldEndTurn) {
		TurnManager::Instance()->endTurn();
	}
}

void ReaperIdleBehaviour::start()
{
	if (enterRoomEventID == -1) {
		enterRoomEventID = Griddy::Events::subscribe(this, &ReaperIdleBehaviour::onPlayerEnterBossRoom);
	}
	Behaviour::start();
}

void ReaperIdleBehaviour::destroy()
{
	if (enterRoomEventID != -1)
	{
		Griddy::Events::unsubscribe(this, &ReaperIdleBehaviour::onPlayerEnterBossRoom, enterRoomEventID);

		enterRoomEventID = -1;
	}
}

void ReaperIdleBehaviour::onPlayerEnterBossRoom(EnterBossRoomEvent* event)
{
	shouldEndTurn = false;
	GameObject* enemy = parentFSM->getOwner();
	for (auto position : event->bossPositions)
	{
		GridSystem::Instance()->setSatOnTile(0, position, enemy);
	}

	//start attack behaviour
	Griddy::Events::invoke<StateTransition>(parentFSM, new ReaperCombatBehaviour(parentFSM, myPos, spawnerPositions));
}

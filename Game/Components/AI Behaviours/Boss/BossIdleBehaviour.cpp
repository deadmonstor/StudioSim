#include "BossIdleBehaviour.h"
#include "Core/Grid/GridSystem.h"
#include "Core/Components\Transform.h"
#include "Core\Components\AI\StateMachine.h"
#include "BossCombatBehaviour.h"

#include "../../TurnManager.h"
#include "../../DelayTask.h"


BossIdleBehaviour::BossIdleBehaviour(StateMachine* parentFSMArg, std::vector<glm::vec2> spawnerPositionsArg)
{
	isInFSM = true;
	parentFSM = parentFSMArg;
	spawnerPositions = spawnerPositionsArg;
}

void BossIdleBehaviour::Act()
{
	if (shouldEndTurn) {
		DelayTask::createTask(parentFSM->getOwner(), 2, [this]()
			{
				TurnManager::Instance()->endTurn();
		LOG_INFO("Boss Idle Behaviour -> DelayTask::createTask -> TurnManager::Instance()->endTurn()");
			});
	}
}

void BossIdleBehaviour::start()
{
	if (enterRoomEventID == -1) {
		enterRoomEventID = Griddy::Events::subscribe(this, &BossIdleBehaviour::onPlayerEnterBossRoom);
	}
	Behaviour::start();
}

void BossIdleBehaviour::destroy()
{
	if (enterRoomEventID != -1)
	{
		Griddy::Events::unsubscribe(this, &BossIdleBehaviour::onPlayerEnterBossRoom, enterRoomEventID);

		enterRoomEventID = -1;
	}
}

void BossIdleBehaviour::onPlayerEnterBossRoom(EnterBossRoomEvent* event)
{
	shouldEndTurn = false;
	GameObject* enemy = parentFSM->getOwner();
	for (auto position : event->bossPositions)
	{
		GridSystem::Instance()->setSatOnTile(0, position, enemy);
	}

	//start attack behaviour
	Griddy::Events::invoke<StateTransition>(parentFSM, new BossCombatBehaviour(parentFSM, spawnerPositions));
}

#include "BossIdleBehaviour.h"

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

BossIdleBehaviour::BossIdleBehaviour(StateMachine* parentFSMArg)
{
	isInFSM = true;
	parentFSM = parentFSMArg;
}

void BossIdleBehaviour::onPlayerEnterBossRoom(EnterBossRoomEvent* event)
{
	//start attack behaviour
	LOG_INFO("Boss Attack!");
}

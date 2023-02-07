#pragma once
#include "Core/Components/AI/Behaviour.h"
#include <Util/Events/Events.h>
#include "..\..\..\GameEvents.h"

class StateMachine;

class BossIdleBehaviour : 
	public Behaviour
{
public:
	void start() override;
	void destroy() override;
	explicit BossIdleBehaviour(StateMachine* parentFSMArg);
private:
	StateMachine* parentFSM;
	void onPlayerEnterBossRoom(EnterBossRoomEvent* event);
protected:
	int8_t enterRoomEventID = -1;
};


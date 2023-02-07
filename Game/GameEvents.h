#pragma once
#include "Util/Events/FunctionHandler.h"

class EnterBossRoomEvent : public Griddy::Event
{
public:
	EnterBossRoomEvent() {}
};
class BossDeathEvent : public Griddy::Event
{
public:
	BossDeathEvent() {}
};
#pragma once
#include "Util/Events/FunctionHandler.h"
#include "glm/vec2.hpp"
#include <vector>


class EnterBossRoomEvent : public Griddy::Event
{
public:
	explicit EnterBossRoomEvent(std::vector<glm::vec2> bossPositionsArg) : bossPositions(bossPositionsArg) {}
	std::vector<glm::vec2> bossPositions;
};
class BossDeathEvent : public Griddy::Event
{
public:
	BossDeathEvent() {}
};
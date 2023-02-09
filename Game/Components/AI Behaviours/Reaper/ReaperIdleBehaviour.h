#pragma once
#include "Core/Components/AI/Behaviour.h"
#include <Util/Events/Events.h>
#include "..\..\..\GameEvents.h"



class StateMachine;

class ReaperIdleBehaviour :
	public Behaviour
{
public:
	explicit ReaperIdleBehaviour(StateMachine* parentFSMArg, glm::vec2 myPosArg, std::vector<glm::vec2> spawnerPositionsArg);
	void Act() override;
	void start() override;
	void destroy() override;
private:
	StateMachine* parentFSM;
	std::vector<glm::vec2> spawnerPositions;
	void onPlayerEnterBossRoom(EnterBossRoomEvent* event);
protected:
	glm::vec2 myPos;
	int8_t enterRoomEventID = -1;
	bool shouldEndTurn = true;
};


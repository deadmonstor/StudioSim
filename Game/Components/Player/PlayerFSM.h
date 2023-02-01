#pragma once
#include "PlayerMovementBehaviour.h"
#include "Core/Components/AI/StateMachine.h"

class PlayerFSM : public StateMachine
{
public:
	void start() override;

};


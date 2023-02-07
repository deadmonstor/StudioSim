#pragma once
#include "Core/Components/AI/Behaviour.h"

class StateMachine;

class BossIdleBehaviour : 
	public Behaviour
{

private:
	void onPlayerEnterBossRoom(Griddy::Event*);
protected:
	FunctionMap CreateFunctionMap() override;
};


#pragma once
#include "../../TurnManager.h"
#include "../Core/Component.h"
#include "../NormalEnemyFSM.h"
#include "..\..\Items\Stats.h"
#include "BossStateMachine.h"

class EnemyComponent : public Component
{
	int onStartTurnID = -1;
private:
	StateMachine* enemyFSM;
	EnemyStats stats;

public:
	EnemyComponent();
	explicit EnemyComponent(StateMachine* stateMachineArg, EnemyStats statsArg);

	void start() override;
	void destroy() override;
	void onTurnChanged(const onStartTurn* event);

	void die();

	EnemyStats getStats() { return stats; }
	int roundsFreeze = 0;

private:
	void DropLoot();

};

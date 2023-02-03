#pragma once
#include "TurnManager.h"
#include "Core/Component.h"
#include "AI Behaviours/NormalEnemyFSM.h"
#include "..\Components\Items\Stats.h"

class EnemyComponent : public Component
{
	int onStartTurnID = -1;
private:
	StateMachine* enemyFSM;
	EnemyStats stats;
	std::string spriteName;
public:
	EnemyComponent();
	explicit EnemyComponent(StateMachine* stateMachineArg, EnemyStats statsArg, std::string spriteNameArg);
	
	void start() override;
	void destroy() override;
	void onTurnChanged(const onStartTurn* event);

	void die();

	EnemyStats getStats() { return stats; }

private:
	void DropLoot();

};

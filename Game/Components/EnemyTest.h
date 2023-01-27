#pragma once
#include "TurnManager.h"
#include "Core/Component.h"
#include "NormalEnemyFSM.h"

class EnemyTest : public Component
{
	int onStartTurnID = -1;
	
public:
	NormalEnemyFSM* enemyFSM;
	void start() override;
	void destroy() override;
	void onTurnChanged(const onStartTurn* event);
};

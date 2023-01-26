#pragma once
#include "TurnManager.h"
#include "Core/Component.h"

class EnemyTest : public Component
{
	int onStartTurnID = -1;
	
public:
	void start() override;
	void destroy() override;
	void onTurnChanged(const onStartTurn* event);
};

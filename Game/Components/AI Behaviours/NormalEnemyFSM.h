#pragma once
#include "Core\Components\AI\StateMachine.h"
#include "EnemyIdleBehaviour.h"
class NormalEnemyFSM :
    public StateMachine
{
public:
    void start() override;
};


#pragma once
#include "Core\Components\AI\StateMachine.h"
#include "BossIdleBehaviour.h"
class BossStateMachine :
    public StateMachine
{
public:
    void start() override;
};
#pragma once
#include "Core\Components\AI\Behaviour.h"
#include "Core\Components\AI\StateMachine.h"
class EnemyIdleBehaviour :
    public Behaviour
{
public:
    EnemyIdleBehaviour();
    EnemyIdleBehaviour(StateMachine* parentFSM);
    void Act() override;
private:
    StateMachine* parentFSM;
};


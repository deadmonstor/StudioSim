#pragma once
#include "Core\Components\AI\Behaviour.h"
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


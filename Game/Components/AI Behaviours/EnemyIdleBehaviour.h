#pragma once
#include "Core/Components/AI/Behaviour.h"

class StateMachine;

class EnemyIdleBehaviour :
    public Behaviour
{
public:
    EnemyIdleBehaviour();
    explicit EnemyIdleBehaviour(StateMachine* parentFSM);
    void Act() override;
private:
    StateMachine* parentFSM;
};


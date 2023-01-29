#pragma once
#include "Core\Components\AI\PlannedBehaviour.h"

class EnemyCombatBehaviour :
    public PlannedBehaviour
{
public:
    EnemyCombatBehaviour();
    EnemyCombatBehaviour(StateMachine* parentFSMArg);
    void WorldAnalysis() override;
    void ActionAnalysis() override;
    void GenerateBehaviourList() override;
    void GenerateEffects() override;
private:
    StateMachine* parentFSM;
};


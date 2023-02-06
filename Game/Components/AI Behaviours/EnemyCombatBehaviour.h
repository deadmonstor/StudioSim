#pragma once
#include "Core/Components/AI/PlannedBehaviour.h"
#include "Core/Components/AI/StateMachine.h"
#include "glm/vec3.hpp"

class EnemyCombatBehaviour :
    public PlannedBehaviour
{
public:
    EnemyCombatBehaviour();
    explicit EnemyCombatBehaviour(StateMachine* parentFSMArg);
    void WorldAnalysis() override;
    void ActionAnalysis() override;
    void GenerateBehaviourList() override;
    void GenerateEffects() override;
    
    void endTurn();
private:
    StateMachine* parentFSM;
};


#pragma once
#include "Core/Components/AI/PlannedBehaviour.h"
#include "Core/Components/AI/StateMachine.h"
#include "glm/vec2.hpp"

class BossCombatBehaviour :
    public PlannedBehaviour
{
public:
    explicit BossCombatBehaviour(StateMachine* parentFSMArg, glm::vec2 myPosArg, std::vector<glm::vec2> spawnerPositionsArg);
    void WorldAnalysis() override;
    void ActionAnalysis() override;
    void GenerateBehaviourList() override;
    void GenerateEffects() override;

    void endTurn();
private:
    StateMachine* parentFSM;
    glm::vec2 myPos;
    std::vector<glm::vec2> spawnerPositions;
};


#pragma once
#include "Core\Components\AI\StateMachine.h"
#include "BossIdleBehaviour.h"
class BossStateMachine :
    public StateMachine
{
public:
    explicit BossStateMachine(glm::vec2 myPosArg, std::vector<glm::vec2> spawnerPositionsArg) : myPos(myPosArg), spawnerPositions(spawnerPositionsArg) {}
    void start() override;
private:
    glm::vec2 myPos;
    std::vector<glm::vec2> spawnerPositions;
};
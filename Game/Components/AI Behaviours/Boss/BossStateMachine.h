#pragma once
#include "Core\Components\AI\StateMachine.h"
#include "BossIdleBehaviour.h"
class BossStateMachine :
    public StateMachine
{
public:
    explicit BossStateMachine(std::vector<glm::vec2> spawnerPositionsArg) : spawnerPositions(spawnerPositionsArg) {}
    void start() override;
private:
    std::vector<glm::vec2> spawnerPositions;
};
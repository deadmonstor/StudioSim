#pragma once
#include "Core\Components\AI\StateMachine.h"
#include "ReaperIdleBehaviour.h"

class ReaperStateMachine :
    public StateMachine
{
public:
    explicit ReaperStateMachine(glm::vec2 myPosArg, std::vector<glm::vec2> spawnerPositionsArg) : myPos(myPosArg), spawnerPositions(spawnerPositionsArg) {}
    void start() override;
    void destroy() override;
private:
    glm::vec2 myPos;
    std::vector<glm::vec2> spawnerPositions;
};
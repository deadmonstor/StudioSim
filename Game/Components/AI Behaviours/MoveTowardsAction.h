#pragma once
#include "Core\Components\AI\Behaviour.h"
#include "Core\Grid\PathfindingMachine.h"
#include "Core\Components\Transform.h"
class MoveTowardsAction :
    public Behaviour
{
public:
    MoveTowardsAction() { parentObject = nullptr; target = glm::vec2(); currentPos = glm::vec2(); }
    MoveTowardsAction(GameObject* parentObjectArg) { parentObject = parentObjectArg; target = glm::vec2(); currentPos = glm::vec2(); }
    void Act() override;
    void SetTarget(glm::vec2 targetArg) { target = targetArg; }
private:
    glm::vec2 target;
    glm::vec2 currentPos;
    GameObject* parentObject;
};


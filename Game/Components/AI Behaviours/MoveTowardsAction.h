#pragma once
#include "Core\Components\AI\Behaviour.h"
#include "Core\Grid\PathfindingMachine.h"

class MoveTowardsAction :
    public Behaviour
{
public:
    MoveTowardsAction();
    explicit MoveTowardsAction(GameObject* parentObjectArg);
    void Act() override;
    void SetTarget(const glm::vec2 targetArg) { target = targetArg; }
private:
    glm::vec2 target;
    glm::vec2 currentPos;
    GameObject* parentObject;

    void endTurn();
    void lerpPosition(GameObject* object, glm::vec2 targetPosition);
};


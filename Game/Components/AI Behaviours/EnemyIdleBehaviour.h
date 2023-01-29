#pragma once
#include "Core/Components/AI/Behaviour.h"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

class EnemyIdleBehaviour :
    public Behaviour
{
public:
    EnemyIdleBehaviour();
    EnemyIdleBehaviour(StateMachine* parentFSM);
    void Act() override;
private:
    StateMachine* parentFSM;

    void endTurn();
    void lerpPosition(GameObject* object, glm::vec2 targetPosition);
    void flashPlayer(GameObject* object, glm::vec3 targetColor);
};


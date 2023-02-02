#pragma once
#include "Core/Components/AI/PlannedBehaviour.h"
#include "Core/Components/AI/StateMachine.h"

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
    
    /*void endTurn();
    void lerpPosition(GameObject* object, glm::vec2 targetPosition);
    void flashPlayer(GameObject* object, glm::vec3 targetColor);

    void EnemyIdleBehaviour::endTurn()
    {
        TurnManager::Instance()->endTurn();
    }

    void EnemyIdleBehaviour::lerpPosition(GameObject* object, const glm::vec2 targetPosition)
    {
        if (!object->hasComponent(typeid(LerpPosition)))
        {
            object->addComponent<LerpPosition>(targetPosition, 3);
        }

        const auto lerpPosition = object->getComponent<LerpPosition>();
        lerpPosition->onLerpComplete = [this]
        {
            endTurn();
        };
        lerpPosition->setSpeed(3);
        lerpPosition->setPosition(targetPosition);
    }

    void EnemyIdleBehaviour::flashPlayer(GameObject* object, const glm::vec3 targetColor)
    {
        Flash::createFlash(object, object->getComponent<AnimatedSpriteRenderer>(), targetColor, 5, [this]
        {
            endTurn();
        });
    }*/
private:
    StateMachine* parentFSM;
};


#pragma once
#include "Core/Components/AI/Behaviour.h"
#include "..\Player\PlayerController.h"
#include "Core\GameObject.h"
#include "Core\Components\Transform.h"
#include <Core/Renderer/ResourceManager.h>

class AttackAction :
    public Behaviour
{
public:
    explicit AttackAction(GameObject* parentObjectArg);
    void Act() override;
    virtual bool IsInRange();
    glm::vec2 FindAttackDirection();
private:
    glm::vec2 attackDirection;
    glm::vec2 currentPos;
    GameObject* parentObject;
    const std::vector<Texture> textureListRST = ResourceManager::GetTexturesContaining("RedSlashThin");

    void createSlashGameObject(glm::vec2 pos);
    void flashPlayer(GameObject* object, const glm::vec3 targetColor);
};


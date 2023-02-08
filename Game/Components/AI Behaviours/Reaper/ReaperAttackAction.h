#pragma once
#include "Core/Components/AI/Behaviour.h"
#include "..\..\Player\PlayerController.h"
#include "Core\GameObject.h"
#include "Core\Components\Transform.h"
#include <Core/Renderer/ResourceManager.h>

class ReaperAttackAction :
    public Behaviour
{
public:
    explicit ReaperAttackAction(glm::vec2 myPosArg, GameObject* parentObjectArg);
    void Act() override;
    std::vector<glm::vec2> FindAttackPositions();

    bool isInRange();
    bool UpdateCooldown();
private:
    int cooldown;
    glm::vec2 currentPos;
    GameObject* parentObject;
    const std::vector<Texture> textureListRST = ResourceManager::GetTexturesContaining("RedSlashThin");

    void createSlashGameObject(glm::vec2 pos);
    void flashPlayer(GameObject* object, const glm::vec3 targetColor);
};
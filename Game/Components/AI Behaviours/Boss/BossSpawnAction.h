#pragma once
#include "Core/Components/AI/Behaviour.h"
#include "..\..\Player\PlayerController.h"
#include "Core\GameObject.h"
#include "Core\Components\Transform.h"
#include <Core/Renderer/ResourceManager.h>

class BossSpawnAction :
    public Behaviour
{
public:
    explicit BossSpawnAction(std::vector<glm::vec2> spawnerPositionsArg);
    void Act() override;
    bool UpdateCooldown();
private:
    int cooldown;
    std::vector<glm::vec2> spawnerPositions;
};

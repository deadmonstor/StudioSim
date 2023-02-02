#pragma once
#include "Core/Scene.h"
#include "glm/vec2.hpp"

class Level2Scene : public Scene
{
    void createEnemy(const glm::vec2 pos);
    
public:
    void init() override;
    void update() override;
    void destroy() override;
};

#pragma once
#include "Core/Scene.h"
#include "glm/vec2.hpp"
#include "Util/Events/EngineEvents.h"

class Level1Scene : public Scene
{
   void createEnemy(const glm::vec2 pos);
    
public:
    void init() override;
    void update() override;
    void destroy() override;
};

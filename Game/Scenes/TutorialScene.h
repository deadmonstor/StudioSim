#pragma once
#include "Core/Scene.h"
#include "glm/vec2.hpp"
#include "Util/Events/EngineEvents.h"

class TutorialScene : public Scene
{
   void createSlime(const glm::vec2 pos);
   void createBoss(const glm::vec2 pos);
public:
    void init() override;
    void update() override;
    void destroy() override;
};

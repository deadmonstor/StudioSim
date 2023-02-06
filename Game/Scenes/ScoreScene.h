#pragma once
#include "Core/Scene.h"
#include "glm/vec2.hpp"
#include "Util/Events/EngineEvents.h"

class ScoreScene : public Scene
{
    int engineRenderID = -1;
    int charKeyDownID = -1;
    int keyDownID = -1;
    std::string playerName;
    bool hasSaved = false;

public:
    void init() override;
    void update() override;
    void destroy() override;

    void onEngineRender(const OnEngineRender* event);
    void OnCharacterKeyDown(const OnCharacterDown* event);
    void OnActualDown(const OnKeyDown* event);
};


#pragma once
#include "Core/Scene.h"
#include "Util/Events/EngineEvents.h"

class MainMenu : public Scene
{
public:
    void init() override;
    void destroy() override;
    
    void onEngineRender(const OnEngineRender* event);
    void onKeyDown(const OnKeyDown* event);
};

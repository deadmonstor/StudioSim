#pragma once
#include "Core/Scene.h"
#include "Core/Components/UI/Panel.h"
#include "Util/Events/EngineEvents.h"

class MainMenu : public Scene
{
    int engineRenderID = -1;
    int keyDownID = -1;
    
public:
    void init() override;
    void destroy() override;
    
    void onEngineRender(const OnEngineRender* event);
    void onKeyDown(const OnKeyDown* event);
};

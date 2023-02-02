#pragma once
#include "Util/SingletonTemplate.h"
#include "Util/Events/EngineEvents.h"

class MainMenu : public SingletonTemplate<MainMenu>
{
public:
    void init();
    void onSceneChanged(const OnSceneChanged* event);
    void onEngineRender(const OnEngineRender* event);
    void onKeyDown(const OnKeyDown* event);
};

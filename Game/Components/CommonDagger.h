#pragma once
#include "Dagger.h"
//#include "Core/Components/Camera.h"
//#include "Util/SingletonTemplate.h"
//#include "Util/Events/EngineEvents.h"

class CommonDagger :
    public Dagger
{
public:
    CommonDagger();

    void createCommonDagger();

    //GameObject* daggerPTR{};
    WeaponStats* commonDaggerStats{};
    
};


#pragma once
#include "Dagger.h"

class CommonDagger :
    public Dagger
{
public:
    CommonDagger();


    //GameObject* daggerPTR{};
    WeaponStats* commonDaggerStats{};
    
};

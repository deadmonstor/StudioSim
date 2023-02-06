#pragma once
#include "Dagger.h"

class CommonDagger :
    public Dagger
{
public:
    CommonDagger();

    std::string name() override { return "Common Dagger"; }
    std::string itemDescription() override { return "Common Dagger"; }
    std::string rarity() override { return "Common"; }
};


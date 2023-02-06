#pragma once
#include "Axe.h"

class CommonAxe :
    public Axe
{
public:
    CommonAxe();
    
    std::string name() override { return "Common Axe"; }
    std::string itemDescription() override { return "A common axe."; }
    std::string rarity() override { return "Common"; }
};


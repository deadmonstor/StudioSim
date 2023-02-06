#pragma once
#include "Hammer.h"

class LegendaryHammer : public Hammer
{
public:
    LegendaryHammer();

    std::string name() override { return "Legendary Hammer"; }
    std::string itemDescription() override { return "A legendary hammer";}
    std::string rarity() override { return "Legendary"; }
};


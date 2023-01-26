#pragma once
#include "StatSystem.h"
#include <string>

struct SpellStats :
    public StatSystem
{
    std::string spellName;
    std::string spellDescription;
    std::string spellType;

    int spellCooldowm;
    int spellLevel;

};


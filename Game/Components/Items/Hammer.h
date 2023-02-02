#pragma once
#include "Weapon.h"
class Hammer :
    public Weapon
{
public:
    Hammer();

    void Attack(glm::fvec2 playerPos, glm::fvec2 attackDir) override;
    void createSlashGameObject(glm::fvec2 pos) override;
    std::list<glm::fvec2> attackPositions;

    WeaponStats* hammerStats{};
};


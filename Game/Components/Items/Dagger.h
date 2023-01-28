#pragma once
#include "Weapon.h"
class Dagger :
    public Weapon
{
public:
    void Attack(glm::fvec2 playerPos, glm::fvec2 attackDir) override;
    void createSlashGameObject(glm::fvec2 pos) override;
};


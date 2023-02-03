#pragma once
#include "Stats.h"
#include "Core/Grid/GridSystem.h"
#include <Core/Components/Health.h>
#include "Core/Components/Transform.h"
#include <Core/Renderer/ResourceManager.h>

class FireBallSpell : public SpellsStats
{
	FireBallSpell();
	void UseSpellAt(glm::fvec2 playerPos, glm::fvec2 attackDir);
	void CreateSpell(glm::fvec2 pos);
	const std::vector<Texture> FireBallTexture = ResourceManager::GetTexturesContaining("Fireball");
	SpellsStats* fireBallStats;
};


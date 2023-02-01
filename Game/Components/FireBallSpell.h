#pragma once
#include "Stats.h"
#include "glm/fwd.hpp"
#include "Core/Renderer/ResourceManager.h"

class FireBallSpell : public SpellsStats
{
	void UseSpellAt(glm::fvec2 playerPos, glm::fvec2 attackDir);
	void CreateSpell(glm::fvec2 pos);
	const std::vector<Texture> FireBallTexture = ResourceManager::GetTexturesContaining("Fire Sprites");
};


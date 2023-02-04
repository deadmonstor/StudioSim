#pragma once
#include "Spell.h"
#include <Core/Renderer/ResourceManager.h>
#include "Core/Grid/GridSystem.h"

class IceSpell : public SpellItem
{
public:
	IceSpell();
	void UseSpell(glm::fvec2 playerPos, glm::fvec2 attackDir) override;

	const int turnsFreeze = 2;
	SpriteComponent* IceSprite;

	std::string name() override { return "Ice Spell"; }
	std::string itemDescription() override { return "Spell that will freeze the enemies"; }
};


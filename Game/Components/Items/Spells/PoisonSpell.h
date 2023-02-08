#pragma once
#include "Spell.h"
#include <Core/Renderer/ResourceManager.h>
#include "Core/Grid/GridSystem.h"
#include "../Stats.h"
#include "Core/Components/Transform.h"
#include "../../LerpPosition.h"
#include "Core/Grid/PathfindingMachine.h"
#include <Core/Renderer/ResourceManager.h>
#include "Core/Grid/GridSystem.h"
#include "../../../System/Inventory.h"

class PoisonSpell :
    public SpellItem
{
public:
	PoisonSpell();
	void UseSpell(glm::fvec2 playerPos, glm::fvec2 attackDir) override;
	

	SpriteComponent* poisonSprite;
	LerpPosition* lerp;
	int turnsPoisoned = 10;

	std::string name() override { return "Poison Spell"; }
	std::string itemDescription() override { return "Spell that will poison the enemies for a certain amount of turns"; }
};


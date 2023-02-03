#pragma once
#include "../Stats.h"
#include "Core/Grid/GridSystem.h"
#include <Core/Components/Health.h>
#include "Core/Components/Transform.h"
#include <Core/Renderer/ResourceManager.h>
#include "../../LerpPosition.h"
#include "../../../System/Inventory.h"
#include "Spell.h"

class FireBallSpell : public SpellItem
{
	
public:
	FireBallSpell();
	void UseSpell(glm::fvec2 playerPos, glm::fvec2 attackDir) override;
	/*void CreateSpell(glm::fvec2 pos);*/
	
	LerpPosition* lerp;
	SpriteComponent* fireBallSprite;

	std::string name() override { return "Fireball Spell"; }
	std::string itemDescription() override { return "FireBall Spell"; }
};


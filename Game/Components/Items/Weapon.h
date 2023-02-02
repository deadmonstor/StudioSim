#pragma once
#include <vector>
#include <Core/Renderer/ResourceManager.h>
#include "Stats.h"
#include "../../System/Inventory.h"
#include "glm/fwd.hpp"

class WeaponItem : public Item
{
public:
	const std::vector<Texture> textureListRST = ResourceManager::GetTexturesContaining("RedSlashThin");
	virtual void Attack(glm::fvec2 playerPos, glm::fvec2 attackDir) {}
	virtual void createSlashGameObject(glm::fvec2 pos) {}
	
	int atk; // Added on to health and strength
	int getAtk() { return atk; }

	int crit;
	int getCrit() { return crit; }

	bool isEquipable() override { return true; }
	ItemType getItemType() override { return ItemType::WEAPON; }
	EquipSlot getEquipSlot() override { return EquipSlot::WEAPON; }
};
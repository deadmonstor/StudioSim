#include "RareAxe.h"

RareAxe::RareAxe()
{
	rareAxeStats = new WeaponStats();
	rareAxeStats->weaponClass = "Axe";
	rareAxeStats->name = "rare axe";
	rareAxeStats->rarity = "rare";
	rareAxeStats->costInShop = 35;
	rareAxeStats->attack = 25;
}


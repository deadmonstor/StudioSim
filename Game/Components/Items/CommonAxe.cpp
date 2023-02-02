#include "CommonAxe.h"

CommonAxe::CommonAxe()
{
	commonAxeStats = new WeaponStats();
	commonAxeStats->name = "common axe";
	commonAxeStats->rarity = "common";
	commonAxeStats->costInShop = 20;
	commonAxeStats->attack = 17;
}

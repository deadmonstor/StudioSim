#include "LegendaryHammer.h"

LegendaryHammer::LegendaryHammer()
{
	legendaryHammerStats = new WeaponStats();
	legendaryHammerStats->name = "legendary hammer";
	legendaryHammerStats->rarity = "legendary";
	legendaryHammerStats->costInShop = 70;
	legendaryHammerStats->attack = 30;
}


#include "CommonSword.h"

CommonSword::CommonSword()
{
	commonSwordStats = new WeaponStats();
	commonSwordStats->name = "common sword";
	commonSwordStats->rarity = "common";
	commonSwordStats->costInShop = 20;
	commonSwordStats->attack = 15;
}


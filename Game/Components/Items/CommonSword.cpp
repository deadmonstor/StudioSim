#include "CommonSword.h"

CommonSword::CommonSword()
{
	commonSwordStats = new WeaponStats();
	commonSwordStats->costInShop = 20;
	commonSwordStats->attack = 15;
}


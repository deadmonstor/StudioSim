#include "RareSword.h"

RareSword::RareSword()
{
	rareSwordStats = new WeaponStats();
	rareSwordStats->weaponClass = "Sword";
	rareSwordStats->name = "rare sword";
	rareSwordStats->rarity = "rare";
	rareSwordStats->costInShop = 30;
	rareSwordStats->attack = 20;
}


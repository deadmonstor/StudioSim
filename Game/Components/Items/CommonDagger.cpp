#include "CommonDagger.h"

CommonDagger::CommonDagger()
{
	commonDaggerStats = new WeaponStats();
	commonDaggerStats->name = "common dagger";
	commonDaggerStats->rarity = "common";
	commonDaggerStats->costInShop = 5;
	commonDaggerStats->attack = 10;
}

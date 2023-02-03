#include "ManaPotion.h"

ManaPotion::ManaPotion()
{
	manaPotionStats = new ConsumableStats();
	manaPotionStats->manaGained = 10;
	manaPotionStats->costInShop = 5;
}

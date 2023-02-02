#include "ManaPotion.h"

ManaPotion::ManaPotion()
{
	manaPotionStats = new ConsumableStats();
	manaPotionStats->name = "mana potion";
	manaPotionStats->manaGained = 10;
	manaPotionStats->costInShop = 5;
}

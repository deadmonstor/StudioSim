#include "ExpPotion.h"

ExpPotion::ExpPotion()
{
	expPotionStats = new ConsumableStats();
	expPotionStats->name = "exp potion";
	expPotionStats->EXPGained = 10;
	expPotionStats->costInShop = 5;
}

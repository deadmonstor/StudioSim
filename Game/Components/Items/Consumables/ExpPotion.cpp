#include "ExpPotion.h"

ExpPotion::ExpPotion()
{
	expPotionStats = new ConsumableStats();
	expPotionStats->EXPGained = 10;
	expPotionStats->costInShop = 5;
}

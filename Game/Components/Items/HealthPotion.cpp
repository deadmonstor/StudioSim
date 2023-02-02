#include "HealthPotion.h"

HealthPotion::HealthPotion()
{
	healthPotionStats = new ConsumableStats();
	healthPotionStats->healthGained = 10;
	healthPotionStats->costInShop = 5;
}

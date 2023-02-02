#include "HealthPotion.h"

HealthPotion::HealthPotion()
{
	healthPotionStats = new ConsumableStats();
	healthPotionStats->name = "health potion";
	healthPotionStats->healthGained = 10;
	healthPotionStats->costInShop = 5;
}

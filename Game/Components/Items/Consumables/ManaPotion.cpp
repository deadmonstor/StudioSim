#include "ManaPotion.h"

ManaPotion::ManaPotion()
{
	manaPotionStats = new ConsumableStats();
	manaPotionStats->manaGained = 10;
	price = 5;
}

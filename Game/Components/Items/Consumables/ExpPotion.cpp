#include "ExpPotion.h"

ExpPotion::ExpPotion()
{
	expPotionStats = new ConsumableStats();
	expPotionStats->EXPGained = 10;
	price = 5;
}

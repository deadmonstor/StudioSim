#include "RareArmour.h"

RareArmour::RareArmour()
{
	rareArmourStats = new ArmourStats();
	rareArmourStats->defence = 2;
	rareArmourStats->health = 5;
	rareArmourStats->mana = 5;
	rareArmourStats->price = 10;
}

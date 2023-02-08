#include "RareArmour.h"

RareArmour::RareArmour()
{
	armour = new ArmourStats();
	armour->defence = 2;
	armour->health = 5;
	armour->mana = 5;
	price = 10;
}

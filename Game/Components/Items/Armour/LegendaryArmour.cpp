#include "LegendaryArmour.h"

LegendaryArmour::LegendaryArmour()
{
	armour = new ArmourStats();
	armour->defence = 3;
	armour->health = 10;
	armour->mana = 10;
	price = 20;
}

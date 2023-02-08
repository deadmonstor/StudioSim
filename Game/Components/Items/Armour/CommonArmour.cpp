#include "CommonArmour.h"

CommonArmour::CommonArmour()
{
	armour = new ArmourStats();
	armour->defence = 1;
	armour->health = 2;
	armour->mana = 2;
	price = 5;
}

#include "CommonArmour.h"

CommonArmour::CommonArmour()
{
	commonArmourStats = new ArmourStats();
	commonArmourStats->defence = 1;
	commonArmourStats->health = 2;
	commonArmourStats->mana = 2;
	commonArmourStats->price = 5;
}

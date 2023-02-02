#include "CommonArmour.h"

CommonArmour::CommonArmour()
{
	commonArmourStats = new ArmourStats();
	commonArmourStats->name = "common armour";
	commonArmourStats->defence = 1;
	commonArmourStats->health = 2;
	commonArmourStats->mana = 2;
	commonArmourStats->costInShop = 5;
}

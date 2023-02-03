#include "LegendaryArmour.h"

LegendaryArmour::LegendaryArmour()
{
	legendaryArmourStats = new ArmourStats();
	legendaryArmourStats->defence = 3;
	legendaryArmourStats->health = 10;
	legendaryArmourStats->mana = 10;
	legendaryArmourStats->costInShop = 20;

}

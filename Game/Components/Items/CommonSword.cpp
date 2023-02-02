#include "CommonSword.h"

CommonSword::CommonSword()
{
}

void CommonSword::createCommonSword()
{
	commonSwordStats->name = "common sword";
	commonSwordStats->rarity = "common";
	commonSwordStats->costInShop = 20;
	commonSwordStats->attack = 15;
}

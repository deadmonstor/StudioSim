#include "ArmourShopItemTile.h"
#include "../Components/Player/PlayerController.h"

bool ArmourShopItemTile::canInteractWith()
{
	return true;
}

//void ArmourShopItemTile::onInteractedWith(TileHolder* curTileHolder)
//{
//	CommonArmour* commonAromur = new CommonArmour();
//	RareArmour* rareArmour = new RareArmour();
//	LegendaryArmour* legendaryArmour = new LegendaryArmour();
//
//	std::vector<Item*> items = { commonAromur };
//	std::string currency = "Gold";
//	Inventory& playerInventory = *PlayerController::Instance()->myInventory;
//	Shop shop(items, currency, playerInventory);
//	shop.purchase(commonAromur, PlayerController::Instance()->playerStats->coinsHeld);
//}

void ArmourShopItemTile::onInteractedWith(TileHolder* curTileHolder)
{
	CommonArmour* commonArmour = new CommonArmour();
	RareArmour* rareArmour = new RareArmour();
	LegendaryArmour* legendaryArmour = new LegendaryArmour();

	std::vector<Item*> items = { commonArmour, rareArmour, legendaryArmour };
	std::string currency = "Gold";
	Inventory& playerInventory = *PlayerController::Instance()->myInventory;
	Shop shop(items, currency, playerInventory);

	std::cout << "Which armor would you like to purchase?" << std::endl;
	std::cout << "1. Common Armor - " << commonArmour->price << " " << currency << std::endl;
	std::cout << "2. Rare Armor - " << rareArmour->price << " " << currency << std::endl;
	std::cout << "3. Legendary Armor - " << legendaryArmour->price << " " << currency << std::endl;

	int choice;
	std::cin >> choice;
	switch (choice) {
	case 1:
		//shop.purchase(commonArmour, PlayerController::Instance()->playerStats->coinsHeld);
		shop.purchase(commonArmour, *PlayerController::Instance()->playerStats);
		break;
	case 2:
		//shop.purchase(rareArmour, PlayerController::Instance()->playerStats->coinsHeld);
		shop.purchase(rareArmour, *PlayerController::Instance()->playerStats);
		break;
	case 3:
		//shop.purchase(legendaryArmour, PlayerController::Instance()->playerStats->coinsHeld);
		shop.purchase(legendaryArmour, *PlayerController::Instance()->playerStats);
		break;
	default:
		std::cout << "Invalid choice. Please enter a number between 1 and 3." << std::endl;
		break;
	}
}

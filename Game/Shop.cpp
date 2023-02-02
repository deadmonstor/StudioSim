#include "Shop.h"

//Shop::Shop(std::vector<Item*> items, std::string currency, Inventory& inventory) : items_(items), currency_(currency), inventory_(inventory) {}
Shop::Shop(int items, std::string currency, Inventory& inventory) : items_(items), currency_(currency), inventory_(inventory) {}

void Shop::displayItems() {
    // Display a list of all items for sale, their prices, and descriptions
    for (auto item : items_) {
        std::cout << item->name() << " - " << item->price << " " << currency_ << std::endl;
        std::cout << item->itemDescription() << std::endl;
    }
}

void Shop::purchase(Item* item, int& playerCurrency) {
    // Check if player has enough currency to make the purchase
    if (playerCurrency < item->price) {
        std::cout << "You do not have enough " << currency_ << " to make this purchase." << std::endl;
        return;
    }

    // Update player's currency and inventory
    playerCurrency -= item->price;
    inventory_.add_item(item);
    std::cout << "Purchase successful! You now have " << playerCurrency << " " << currency_ << " remaining." << std::endl;
}

void Shop::sell(Item* item, int& playerCurrency) {
    // Check if item is in player's inventory
    if (!inventory_.remove_item(item)) {
        std::cout << "You do not have this item in your inventory." << std::endl;
        return;
    }

    // Update player's currency
    playerCurrency += item->price;
    std::cout << "Sell successful! You now have " << playerCurrency << " " << currency_ << "." << std::endl;
}
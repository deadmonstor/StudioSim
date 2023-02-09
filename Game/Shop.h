#pragma once

#include "System/Inventory.h"
#include "Components/Items/Stats.h"
#include <iostream>

class Shop {

public:
    Shop(std::vector<Item*> items, std::string currency, Inventory& inventory);
    //Shop(int items, std::string currency, Inventory& inventory);

    void displayItems();
    void purchase(Item* item, PlayerStats& playerStats);
    void purchase(Item* item, int& playerStats);
    void sell(Item* item, int &playerCurrency);

private:
    std::vector<Item*> items_;
    std::string currency_;
    Inventory& inventory_;
};


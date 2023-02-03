#pragma once
#include <string>

struct Item
{
	std::string name;
	std::string type;
	std::string itemDescription;
	std::string rarity;
	bool isEquipped;
	int price;
	int getPrice() { return price; }

	bool isUsable;
	virtual ~Item() {}; // added virtual destructor
};


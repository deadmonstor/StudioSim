#pragma once
struct ItemInfo
{
	int price;
	virtual int getPrice() { return price; }
};

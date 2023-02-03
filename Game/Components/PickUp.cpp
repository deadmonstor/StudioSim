#include "PickUp.h"

int PickUp::GetAmount()
{
	return Amount;
}

void PickUp::SetAmount(int ValueIn)
{
	Amount = ValueIn;
}


std::string PickUp::GetItemName()
{
	return ItemName;
}

void PickUp::SetItemName(std::string inputName)
{
	ItemName = inputName;
}



PickUp::PickUp()
{
	
}
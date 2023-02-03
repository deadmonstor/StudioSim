#pragma once
#include <string>
#include "Core/Component.h"

class PickUp : public Component
{
public:
	int GetAmount();
	void SetAmount(int ValueIn);
	std::string GetItemName();
	void SetItemName(std::string inputName);
	PickUp();

private:
	int Amount;
	std::string ItemName;
};


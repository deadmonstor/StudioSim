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

	void update();

	void CheckCollisions();

private:
	int Amount = 1;
	std::string ItemName;
	int Counter = 0;
	GameObject* m_playerPTR;
};


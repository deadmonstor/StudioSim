#include "PickUp.h"
#include "Core/PhysicsSystem.h"
#include "Player/PlayerController.h"
#include <iostream>


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
	m_playerPTR = PlayerController::Instance()->playerPTR;
	//this->getOwner()
	//Add a collision box to the item the size of one tile (48*48)
	//Add a collision box on the player, when they overlap the item is picked up added to the inventory and the game objected is deleted.
}

void PickUp::update()
{
	if (getOwner() == nullptr || PlayerController::Instance()->playerPTR == nullptr)
	{
		std::cout << "NullPtr\n";
	}
	else
	{
		CheckCollisions();
	}
}


void PickUp::CheckCollisions()
{
	
	if (PhysicsSystem::Instance()->checkBoxCollision(*getOwner()->getTransform(), *m_playerPTR->getTransform())) //PlayerController::Instance()->playerPTR->
	{
		std::cout << "CollidedWith\n";
		if (getOwner()->getName().contains("money"))
		{
			PlayerController::Instance()->AddCoins(Amount);
			SceneManager::Instance()->destroyGameObject(getOwner());
		}


		return;
	}
	//std::cout << "Stopped Colliding\n";
}
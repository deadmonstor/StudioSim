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
	
	//this->getOwner()
	//Add a collision box to the item the size of one tile (48*48)
	//Add a collision box on the player, when they overlap the item is picked up added to the inventory and the game objected is deleted.
}

void PickUp::update()
{
	//PhysicsSystem::Instance()->checkBoxCollision(*getOwner(), *PlayerController::Instance()->playerPTR);
	/*if (PhysicsSystem::Instance()->checkBoxCollision(*getOwner(), *PlayerController::Instance()->playerPTR))
	{
		std::cout << "CollidedWith\n";
	}*/
	//std::cout << "CollidedWith\n";
	if (getOwner() == nullptr || PlayerController::Instance()->playerPTR == nullptr)
	{
		std::cout << "NullPtr\n";
	}
	else
	{
		CheckCollisions();
	}
	/*else if (PhysicsSystem::Instance()->checkBoxCollision(*getOwner(), *PlayerController::Instance()->playerPTR))
	{
		std::cout << "CollidedWith\n";
	}*/
}


void PickUp::CheckCollisions()
{
	/*if (getOwner() == nullptr || PlayerController::Instance()->playerPTR == nullptr)
	{
		std::cout << "NullPtr\n";
	}*/
	if (PhysicsSystem::Instance()->checkBoxCollision(*getOwner()->getTransform(), *PlayerController::Instance()->playerPTR->getTransform()))
	{
		std::cout << "CollidedWith\n";
		return;
	}
	std::cout << "Stopped Colliding\n";
}
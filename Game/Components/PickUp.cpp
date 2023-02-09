#include "PickUp.h"
#include "Core/PhysicsSystem.h"
#include "Player/PlayerController.h"
#include "../System/Inventory.h"
#include <iostream>
#include <Core/Renderer/ResourceManager.h>
#include <Core/AudioEngine.h>

#include "../ScoreSystem.h"


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
	if (PhysicsSystem::Instance()->checkBoxCollision(*getOwner()->getTransform(), *m_playerPTR->getTransform()))
	{
		if (getOwner()->getName().contains("money"))
		{
			PlayerController::Instance()->AddCoins(Amount);
			ScoreSystem::Instance()->addGoldEarned(Amount);
			
			if (!ResourceManager::HasSound("Sounds\\coinPickUpSound.wav"))
				AudioEngine::Instance()->loadSound("Sounds\\coinPickUpSound.wav", FMOD_3D);

			AudioEngine::Instance()->playSound("Sounds\\coinPickUpSound.wav", false, 0.05f, 0, 0, AudioType::SoundEffect);
			
			SceneManager::Instance()->destroyGameObject(getOwner());
		}
		else if (Inventory::getItemByName.contains(getOwner()->getName()))
		{
			if (PlayerController::Instance()->myInventory->add_item(Inventory::getItemByName[getOwner()->getName()]()))
			{
				if (!ResourceManager::HasSound("Sounds\\pickUpSound.wav"))
					AudioEngine::Instance()->loadSound("Sounds\\pickUpSound.wav", FMOD_3D);

				AudioEngine::Instance()->playSound("Sounds\\pickUpSound.wav", false, 0.1f, 0, 0, AudioType::SoundEffect);
				SceneManager::Instance()->destroyGameObject(getOwner());
			}
		}else
		{
			LOG_ERROR("Item cannot be added to inventory " + getOwner()->getName());
		}
	}
}
#include "PlayerSpellBehaviour.h"
#include "PlayerMovementBehaviour.h"
#include "../TurnManager.h"
#include "../../Components/Items/Spells/Spell.h"
#include "../../System/Inventory.h"

PlayerSpellBehaviour::PlayerSpellBehaviour()
{
	isInFSM = false;
	map = CreateFunctionMap();
	
}

PlayerSpellBehaviour::PlayerSpellBehaviour(bool isInFSMParam)
{
	isInFSM = isInFSMParam;
	map = CreateFunctionMap();
}

void PlayerSpellBehaviour::Act()
{
	if (willFlashOnce) return;
	currentPlayerPos = (PlayerController::Instance()->playerPTR->getTransform()->getPosition()) / GridSystem::Instance()->getTileSize();
	if (Item* spell = PlayerController::Instance()->myInventory->getFirstItemWithEquipSlot(EquipSlot::SPELL); spell != nullptr)
	{
		const auto spellCasted = dynamic_cast<SpellItem*>(spell);
		spellCasted->UseSpell(currentPlayerPos, attackDir);
		PlayerController::Instance()->playerStats->currentMana -= spellCasted->spellStats->manaCost;

		if (TurnManager::Instance()->isCurrentTurnObject(PlayerController::Instance()->playerPTR) && !willFlashOnce)
		{
			spellCasted->spellStats->currentCooldown = 0;
			//TurnManager::Instance()->endTurn();
		}
	}
	/*fireBall = new FireBallSpell();
	fireBall->UseSpellAt(currentPlayerPos, attackDir);*/
}

void PlayerSpellBehaviour::onKeyDownResponse(Griddy::Event* event)
{
	OnKeyDown* eventCasted = static_cast<OnKeyDown*>(event);

	if (eventCasted->key == GLFW_KEY_Q)
	{
		Griddy::Events::invoke<OnPlayerControllerFSMUpdate>("PlayerMovementBehaviour");
		Griddy::Events::invoke<StateTransition>((StateMachine*)PlayerController::Instance()->playerFSM, new PlayerMovementBehaviour(true));
	}

	if (eventCasted->key == GLFW_KEY_E)
	{
		Griddy::Events::invoke<OnPlayerControllerFSMUpdate>("PlayerAttackBehaviour");
		Griddy::Events::invoke<StateTransition>((StateMachine*)PlayerController::Instance()->playerFSM, new PlayerAttackBehaviour(true));
	}

	if (eventCasted->key == GLFW_KEY_W)
	{
		attackDir.y = 1;
	}
	else if (eventCasted->key == GLFW_KEY_S)
	{
		attackDir.y = -1;
	}
	else if (eventCasted->key == GLFW_KEY_A)
	{
		attackDir.x = -1;
	}
	else if (eventCasted->key == GLFW_KEY_D)
	{
		attackDir.x = 1;
	}

	if (eventCasted->key == GLFW_KEY_W || eventCasted->key == GLFW_KEY_S ||
		eventCasted->key == GLFW_KEY_A || eventCasted->key == GLFW_KEY_D)
	{
		Item* spell = PlayerController::Instance()->myInventory->getFirstItemWithEquipSlot(EquipSlot::SPELL);
		
		if ((TurnManager::gNoclipMode || TurnManager::Instance()->isCurrentTurnObject(PlayerController::Instance()->playerPTR)) /*&&
			 spell != nullptr*/)
		{
			if (PlayerController::Instance()->playerStats->currentMana > 0)
			{
				if (Item* spell = PlayerController::Instance()->myInventory->getFirstItemWithEquipSlot(EquipSlot::SPELL); spell != nullptr)
				{
					const auto spellCasted = dynamic_cast<SpellItem*>(spell);

					if (spellCasted->spellStats->currentCooldown == spellCasted->spellStats->maxCooldown && 
						spellCasted->spellStats->manaCost <= PlayerController::Instance()->playerStats->currentMana)
					{
						Act();
					}
				}
			
			}
			/*const auto spellCasted = dynamic_cast<SpellItem*>(spell);
			if (spellCasted->getCoolDown() != 0)
			{
				
			}*/
		}
	}
	attackDir = glm::fvec2(0, 0);
}

void PlayerSpellBehaviour::onKeyUpResponse(Griddy::Event*)
{
	//canThrowSpell = true;
}

FunctionMap PlayerSpellBehaviour::CreateFunctionMap()
{
	FunctionMap map = {};
	map[typeid(OnKeyDown)] =
		[](Behaviour* pointer, Griddy::Event* event)
	{
		dynamic_cast<PlayerSpellBehaviour*>(pointer)->onKeyDownResponse(event);
	};
	map[typeid(OnKeyUp)] =
		[](Behaviour* pointer, Griddy::Event* event)
	{
		dynamic_cast<PlayerSpellBehaviour*>(pointer)->onKeyUpResponse(event);
	};

	return map;
}

#include "EnemyCombatBehaviour.h"

#include "MoveTowardsAction.h"
#include "../DelayTask.h"
#include "../Player/PlayerController.h"
#include "Core/Components/Transform.h"
#include "Core/Grid/PathfindingMachine.h"
#include "../TurnManager.h"
#include "../Core/Components/AnimatedSpriteRenderer.h"
#include "AttackAction.h"

EnemyCombatBehaviour::EnemyCombatBehaviour()
	: PlannedBehaviour()
{
	isInFSM = false;
	parentFSM = nullptr;
}

EnemyCombatBehaviour::EnemyCombatBehaviour(StateMachine* parentFSMArg)
	: PlannedBehaviour()
{
	parentFSM = parentFSMArg;
	isInFSM = true;
	
}

void EnemyCombatBehaviour::WorldAnalysis()
{
	//Check collisions with the attack behaviour's attack tiles and the player. This toggles between the InRange and OutOfRange effects
	bool inRange = static_cast<AttackAction*>(availableActions["Attack"].second)->IsInRange();
	if (inRange)
	{
		effects["OutOfRange"].active = false;
		effects["InRange"].active = true;
	}
	else {
		effects["OutOfRange"].active = true;
		effects["InRange"].active = false;
	}
}

void EnemyCombatBehaviour::ActionAnalysis()
{
	PlannedBehaviour::ActionAnalysis();

	if (fittestAction == availableActions["MoveTowards"].second)
	{
		//Set the closest available tile to the player as the target for the move towards action
		const glm::vec2 playerPos = PlayerController::Instance()->playerPTR->getTransform()->getPosition();
		const glm::vec2 myPos = parentFSM->getOwner()->getTransform()->getPosition();
		const glm::vec2 tileSize = GridSystem::Instance()->getTileSize();
		const TileHolder* targetTile = nullptr;
		int depth = 0;
		while (targetTile == nullptr)
		{
			//int startDepth = (depth - 1 < 0) ? 0 : depth - 1;
			const TileHolder* closestEmptyTile = PathfindingMachine::Instance()->FindClosestEmptyTile(myPos, playerPos, depth, 0);

			if (closestEmptyTile != nullptr)
				targetTile = closestEmptyTile;

			depth++;
		}

		static_cast<MoveTowardsAction*>(availableActions["MoveTowards"].second)->SetTarget(targetTile->position * tileSize);
	}
}
//Create and initialize behaviours
void EnemyCombatBehaviour::GenerateBehaviourList()
{
	availableActions["Attack"] = std::make_pair(0, new AttackAction(parentFSM->getOwner()));
	availableActions["MoveTowards"] = std::make_pair(0, new MoveTowardsAction(parentFSM->getOwner()));
	for (auto action : availableActions)
	{
		if (!action.second.second->GetInitValue())
		{
			availableActions["MoveTowards"].second->start();
		}
	}
}

void EnemyCombatBehaviour::GenerateEffects()
{
	//Add the inRange effect which will put influence on the attack action
	effects["InRange"] = Effect();
	effects["InRange"].influencedActions["Attack"] = std::make_pair(5, availableActions["Attack"].second);
	effects["InRange"].influencedActions["MoveTowards"] = std::make_pair(-5, availableActions["MoveTowards"].second);

	effects["OutOfRange"] = Effect();
	effects["OutOfRange"].influencedActions["MoveTowards"] = std::make_pair(1, availableActions["MoveTowards"].second);
}

void EnemyCombatBehaviour::endTurn()
{
	TurnManager::Instance()->endTurn();
	LOG_INFO("EnemyCombatBehaviour::endTurn() - Enemy turn ended");
}

void EnemyCombatBehaviour::flashPlayer(GameObject* object, const glm::vec3 targetColor)
{
	Flash::createFlash(object, object->getComponent<AnimatedSpriteRenderer>(), targetColor, 5, [this]
	{
		endTurn();
		LOG_INFO("EnemyCombatBehaviour::flashPlayer() - Flash ended");
	});
}
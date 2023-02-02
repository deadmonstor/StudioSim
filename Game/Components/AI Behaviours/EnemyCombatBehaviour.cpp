#include "EnemyCombatBehaviour.h"

#include "MoveTowardsAction.h"
#include "../DelayTask.h"
#include "../Player/PlayerController.h"
#include "Core/Components/Transform.h"
#include "Core/Grid/PathfindingMachine.h"
#include "../TurnManager.h"
#include "../Flash.h"
#include "../Core/Components/AnimatedSpriteRenderer.h"

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

	effects["OutOfRange"].active = true;


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
	
	availableActions["MoveTowards"] = std::make_pair(0, new MoveTowardsAction(parentFSM->getOwner()));
	availableActions["Attack"] = std::make_pair(0, new Behaviour());
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
}

void EnemyCombatBehaviour::flashPlayer(GameObject* object, const glm::vec3 targetColor)
{
	Flash::createFlash(object, object->getComponent<AnimatedSpriteRenderer>(), targetColor, 5, [this]
	{
		endTurn();
	});
}
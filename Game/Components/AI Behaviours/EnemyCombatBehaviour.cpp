#include "EnemyCombatBehaviour.h"

#include "MoveTowardsAction.h"
#include "../Player/PlayerController.h"
#include "Core/Components/Transform.h"
#include "Core/Grid/PathfindingMachine.h"

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
	
}

void EnemyCombatBehaviour::ActionAnalysis()
{
	PlannedBehaviour::ActionAnalysis();
	//Set the player position as the target for the move towards action
	dynamic_cast<MoveTowardsAction*>(availableActions["MoveTowards"].second)->SetTarget(PlayerController::Instance()->playerPTR->getTransform()->getPosition());
}

void EnemyCombatBehaviour::GenerateBehaviourList()
{
	//Create and initialize move towards behaviour
	availableActions["MoveTowards"] = std::make_pair(0, new MoveTowardsAction(parentFSM->getOwner()));
	if (!availableActions["MoveTowards"].second->GetInitValue())
	{
		availableActions["MoveTowards"].second->start();
	}
}

void EnemyCombatBehaviour::GenerateEffects()
{
}

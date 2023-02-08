#include "BossCombatBehaviour.h"
#include "../../TurnManager.h"
#include "BossAttackAction.h"
#include "../DoNothingAction.h"
#include "BossSpawnAction.h"

BossCombatBehaviour::BossCombatBehaviour(StateMachine* parentFSMArg, glm::vec2 myPosArg, std::vector<glm::vec2> spawnerPositionsArg)
{
	isInFSM = true;
	parentFSM = parentFSMArg;
	myPos = myPosArg;
	spawnerPositions = spawnerPositionsArg;
}

void BossCombatBehaviour::WorldAnalysis()
{
	bool spawnerOffCooldown = static_cast<BossSpawnAction*>(availableActions["Spawn"].second)->UpdateCooldown();
	if (spawnerOffCooldown)
		effects["SpawnOffCooldown"].active = true;
	else
		effects["SpawnOffCooldown"].active = false;

	bool attackOffCooldown = static_cast<BossAttackAction*>(availableActions["Attack"].second)->UpdateCooldown();
	bool attackInRange = static_cast<BossAttackAction*>(availableActions["Attack"].second)->isInRange();
	if (attackOffCooldown && attackInRange)
		effects["AttackAvailable"].active = true;
	else
		effects["AttackAvailable"].active = false;
	if (!spawnerOffCooldown && (!attackOffCooldown || !attackInRange))
		effects["NothingAvailable"].active = true;
	else
		effects["NothingAvailable"].active = false;
}

void BossCombatBehaviour::ActionAnalysis()
{
	PlannedBehaviour::ActionAnalysis();
}

void BossCombatBehaviour::GenerateBehaviourList()
{
	availableActions["Attack"] = std::make_pair(0, new BossAttackAction(myPos, parentFSM->getOwner()));
	availableActions["DoNothing"] = std::make_pair(0, new DoNothingAction());
	availableActions["Spawn"] = std::make_pair(0, new BossSpawnAction(spawnerPositions));
	for (auto action : availableActions) 
	{
		if (!action.second.second->GetInitValue())
		{
			action.second.second->start();
		}
	}
}

void BossCombatBehaviour::GenerateEffects()
{
	effects["AttackAvailable"] = Effect();
	effects["SpawnOffCooldown"] = Effect();
	effects["AttackInRange"] = Effect();
	effects["NothingAvailable"] = Effect();

	effects["NothingAvailable"].influencedActions["DoNothing"] = std::make_pair(10, availableActions["DoNothing"].second);

	effects["AttackAvailable"].influencedActions["DoNothing"] = std::make_pair(-10, availableActions["DoNothing"].second);
	effects["AttackAvailable"].influencedActions["Attack"] = std::make_pair(5, availableActions["Attack"].second);


	effects["SpawnOffCooldown"].influencedActions["DoNothing"] = std::make_pair(-10, availableActions["DoNothing"].second);
	effects["SpawnOffCooldown"].influencedActions["Spawn"] = std::make_pair(20, availableActions["Spawn"].second);
}

void BossCombatBehaviour::endTurn()
{
	TurnManager::Instance()->endTurn();
	LOG_INFO("BossCombatBehaviour::endTurn() - Enemy turn ended");
}

#include "DoNothingAction.h"
#include "../TurnManager.h"

void DoNothingAction::Act()
{
	TurnManager::Instance()->endTurn();
}

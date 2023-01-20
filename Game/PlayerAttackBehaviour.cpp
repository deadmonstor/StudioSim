#include "PlayerAttackBehaviour.h"

PlayerAttackBehaviour::PlayerAttackBehaviour(bool isInFSMParam)
{
	isInFSM = isInFSMParam;
	map = CreateFunctionMap();
}

void PlayerAttackBehaviour::Act()
{
}

void PlayerAttackBehaviour::onAttackKeyDown(Griddy::Event*)
{
}

void PlayerAttackBehaviour::onAttackKeyUp(Griddy::Event*)
{
}

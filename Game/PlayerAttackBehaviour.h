#pragma once
#include "Core\Components\AI\Behaviour.h"

class PlayerAttackBehaviour : public Behaviour
{
public:
	PlayerAttackBehaviour() { isInFSM = false; map = CreateFunctionMap(); }
	PlayerAttackBehaviour(bool isInFSMParam);
private:
	void Act() override;
	void onAttackKeyDown(Griddy::Event*);
	void onAttackKeyUp(Griddy::Event*);

};


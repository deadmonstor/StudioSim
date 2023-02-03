#pragma once
#include "Core/Components/AI/Behaviour.h"
#include "PlayerController.h"
#include "glm/fwd.hpp"  
#include "../Items/Spells/FireBallSpell.h"

class PlayerSpellBehaviour : public Behaviour
{
public:
	PlayerSpellBehaviour();
	PlayerSpellBehaviour(bool isInFSMParam);
	
	glm::fvec2 attackDir;
	glm::fvec2 currentPlayerPos;
	bool canThrowSpell = true;
	FireBallSpell* fireBall;

private:
	void Act() override;
	void onKeyDownResponse(Griddy::Event*);
	void onKeyUpResponse(Griddy::Event*);
	bool willFlashOnce = false;
protected:
	FunctionMap CreateFunctionMap() override;
};


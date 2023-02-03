#pragma once
#include "Core/Components/AI/Behaviour.h"
#include "PlayerController.h"
#include "glm/fwd.hpp"  

class PlayerSpellBehaviour : public Behaviour
{
public:
	PlayerSpellBehaviour();
	PlayerSpellBehaviour(bool isInFSMParam);
	
	glm::fvec2 attackDir;
	glm::fvec2 currentPlayerPos;
	bool canThrowSpell = true;
	

private:
	void Act() override;
	void update() override;
	void onKeyDownResponse(Griddy::Event*);
	void onKeyUpResponse(Griddy::Event*);
	bool willFlashOnce = false;
protected:
	FunctionMap CreateFunctionMap() override;
};


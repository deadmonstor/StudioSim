#pragma once
#include "Core\Components\AI\Behaviour.h"
#include "PlayerController.h"


enum Weapon
{
	Dagger,
	Sword,
	Hammer,
	Axe
};

class PlayerAttackBehaviour : public Behaviour
{
public:
	PlayerAttackBehaviour() { isInFSM = false; map = CreateFunctionMap(); }
	PlayerAttackBehaviour(bool isInFSMParam);
	glm::fvec2 attackDir;
	glm::fvec2 currentPlayerPos;
	std::list<glm::fvec2> attackPositions;
	const std::vector<Texture> textureListRST = ResourceManager::GetTexturesContaining("RedSlashThin");
	Weapon weaponClassEquipped;
	bool canAttack;
private:
	void Act() override;
	void onKeyDownResponse(Griddy::Event*);
	void onKeyUpResponse(Griddy::Event*);
	

protected:
	FunctionMap CreateFunctionMap() override;
};



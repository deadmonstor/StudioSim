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
	glm::fvec2 moveDir;
	glm::fvec2 currentPlayerPos;
	const std::vector<Texture> textureListRST = ResourceManager::GetTexturesContaining("RedSlashThin");
	Weapon weaponClassEquipped = Dagger;
private:
	void Act() override;
	void onKeyDownResponse(Griddy::Event*);
	void onKeyUpResponse(Griddy::Event*);
	

protected:
	FunctionMap CreateFunctionMap() override;
};



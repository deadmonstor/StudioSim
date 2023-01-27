#pragma once
#include "Core\Components\AI\Behaviour.h"
#include "PlayerController.h"
#include "Core/Renderer/ResourceManager.h"
#include "glm/fwd.hpp"


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
	PlayerAttackBehaviour();
	PlayerAttackBehaviour(bool isInFSMParam);
	glm::fvec2 attackDir;
	glm::fvec2 currentPlayerPos;
	std::list<glm::fvec2> attackPositions;
	const std::vector<Texture> textureListRST = ResourceManager::GetTexturesContaining("RedSlashThin");
	Weapon weaponClassEquipped;
	bool canAttack = true;
	void AttackOnMovement(glm::fvec2 dir);
	
private:
	void Act() override;
	void onKeyDownResponse(Griddy::Event*);
	void onKeyUpResponse(Griddy::Event*);
	void createSlashGameObject(glm::fvec2 pos);

protected:
	FunctionMap CreateFunctionMap() override;
};



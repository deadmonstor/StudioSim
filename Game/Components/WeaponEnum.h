#pragma once
#include <list>
#include <vector>
#include "Stats.h"
#include "glm/fwd.hpp"
#include <Core/Renderer/ResourceManager.cpp>

class WeaponEnum
{
public:
	const std::vector<Texture> textureListRST = ResourceManager::GetTexturesContaining("RedSlashThin");
	virtual void Attack(glm::fvec2 playerPos, glm::fvec2 attackDir) {};
	virtual void createSlashGameObject(glm::fvec2 pos) {};
};


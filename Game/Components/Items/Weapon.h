#pragma once
#include <vector>
#include <Core/Renderer/ResourceManager.cpp>
#include "glm/fwd.hpp"

class Weapon
{
public:
	const std::vector<Texture> textureListRST = ResourceManager::GetTexturesContaining("RedSlashThin");
	virtual void Attack(glm::fvec2 playerPos, glm::fvec2 attackDir) {}
	virtual void createSlashGameObject(glm::fvec2 pos) {}
};


#pragma once
#include <vector>

#include "Util/SingletonTemplate.h"

class GameObject;

class Scene
{
public:
	std::vector<GameObject*> gameObjects;
};

#pragma once
#include <vector>

class GameObject;

class Scene
{
public:
	std::string name;
private:
	std::vector<GameObject*> gameObjects;
	friend class SceneManager;
	friend class ImGuiHandler;
};

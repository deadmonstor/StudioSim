#pragma once
#include <vector>
#include <string>

class GameObject;

class Scene
{
public:
	std::string name;
private:
	std::vector<GameObject*> gameObjects;
	friend class SceneManager;
	friend class ImGuiHandler;

	virtual void init() {}
	virtual void update() {}
	virtual void destroy() {}
};

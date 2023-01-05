#pragma once
#include <vector>

class Component;

class GameObject
{
	std::vector<Component*> components;
	
private:
	GameObject();
	
public:

	~GameObject();
	
	void start();
	void update();
	void lateUpdate();
	void render();

	void addComponent(Component* component);

	friend class SceneManager;
};

#pragma once
#include <vector>

class Component;

class GameObject
{
	std::vector<Component*> components;
	
	GameObject();
	
	template<class T>
	T *getComponent();
	
	bool isInitialized = false;
public:
	~GameObject();
	
	void start();
	void update();
	void lateUpdate();
	void render();

	void addComponent(Component *component);

	// TODO: Move this when below works
	Component *hasComponentInternal(const type_info &type_info) const;
	bool hasComponent(const type_info &type_info) const;

	friend class SceneManager;
};


#pragma once
#include <list>

class Transform;
class Component;

class GameObject
{
	std::list<Component*> components;
	
	GameObject();
	Transform* transform;
	
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

	Transform* getTransform() const { return transform; }

	friend class SceneManager;
};


#pragma once
#include <list>

class Transform;
class Component;

class GameObject
{
	std::list<Component*> components;
	
	GameObject();
	Transform* transform;
	Component* hasComponentInternal(const type_info &type_info) const;
	
	bool isInitialized = false;
public:
	~GameObject();
	
	void start();
	void update();
	void lateUpdate();

	
	Transform* getTransform() const { return transform; }
	void addComponent(Component *component);
	bool hasComponent(const type_info &type_info) const;
	
	template <typename T>
	T* getComponent()
	{
		if (Component* component = hasComponentInternal(typeid(T)); component != nullptr)
		{
			return static_cast<T*>(component);
		}

		return nullptr;
	}
	
	friend class SceneManager;
};


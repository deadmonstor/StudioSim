﻿#pragma once
#include <list>
#include "Component.h"

class Transform;

class GameObject
{
	std::list<Component*> components;
	
	GameObject();
	Transform* transform{};
	[[nodiscard]] Component* hasComponentInternal(const type_info &type_info) const;
	
	bool isInitialized = false;
	void addComponent(Component* component);
public:
	~GameObject();
	
	void start();
	void update();
	void lateUpdate();

	[[nodiscard]] Transform* getTransform() const { return transform; }
	
	template<typename T, typename... Args>
	std::enable_if_t<std::is_base_of_v<Component, T>, T*> addComponent(Args... args)
	{
		T* newComponent = new T(args...);
		newComponent->owner = this;
	
		if (isInitialized)
			newComponent->start();
		
		components.push_back(newComponent);
		return newComponent;
	}

	[[nodiscard]] bool hasComponent(const type_info &type_info) const;
	
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


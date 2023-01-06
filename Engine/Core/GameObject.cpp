#include "GameObject.h"
#include <typeinfo>
#include "Component.h"
#include "Util/Logger.h"

GameObject::GameObject() = default;

GameObject::~GameObject()
{
	for (const Component* curComponent : components)
	{
		delete curComponent;
		curComponent = nullptr;
	}
}

void GameObject::start()
{
	for (Component* curComponent : components)
	{
		curComponent->start();
	}
}

void GameObject::update()
{
	for (Component* curComponent : components)
	{
		curComponent->update();
	}
}

void GameObject::lateUpdate()
{
	for (Component* curComponent : components)
	{
		curComponent->lateUpdate();
	}
}

void GameObject::addComponent(Component *component)
{
	component->owner = this;
	
	if (isInitialized)
		component->start();

	components.push_back(component);
}

bool GameObject::hasComponent(const std::type_info &type_info) const
{
	return hasComponentInternal(type_info) != nullptr;
}

Component* GameObject::hasComponentInternal(const std::type_info &type_info) const
{
	for (Component* curComponent : components)
	{
		if (typeid(*curComponent) == type_info)
		{
			return curComponent;
		}
	}

	return nullptr;
}

// TODO: Why can't we use this :(
template <class T>
T* GameObject::getComponent()
{
	if (Component *component = hasComponentInternal(typeid(T)); component != nullptr)
	{
		return dynamic_cast<T*>(component);
	}

	return nullptr;
}
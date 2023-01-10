#include "GameObject.h"
#include <typeinfo>
#include "Component.h"
#include "Util/Logger.h"
#include "Util/Events/Events.h"

GameObject::GameObject() = default;

GameObject::~GameObject()
{
	for (const Component* curComponent : components)
	{
		delete curComponent;
		curComponent = nullptr;
	}
}

void GameObject::destroy()
{
	Griddy::Events::invoke<OnGameObjectRemoved>(this);

	for (Component* curComponent : components)
	{
		curComponent->destroy();
	}

	transform = nullptr;
}

void GameObject::start()
{
	for (Component* curComponent : components)
	{
		if (isBeingDeleted()) return;
		curComponent->start();
	}
}

void GameObject::update()
{
	for (Component* curComponent : components)
	{
		if (isBeingDeleted()) return;
		curComponent->update();
	}
}

void GameObject::lateUpdate()
{
	for (Component* curComponent : components)
	{
		if (isBeingDeleted()) return;
		curComponent->lateUpdate();
	}
}

void GameObject::addComponent(Component* component)
{
	component->setOwner(this);
	
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
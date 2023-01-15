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
		#ifdef _DEBUG_ECS
			LOG_INFO("Deleting component " + curComponent->getName() + " for gameobject " + getName());
		#endif
		
		delete curComponent;
		curComponent = nullptr;
	}
}

void GameObject::destroy()
{
	Griddy::Events::invoke<OnGameObjectRemoved>(this);

	for (Component* curComponent : components)
	{
		#ifdef _DEBUG_ECS
		{
			LOG_INFO("Destroying component " + curComponent->getName() + " for gameobject " + getName());
		}
		#endif
		
		curComponent->destroy();
	}
}

void GameObject::start()
{
	if (isBeingDeleted()) return;
	for (Component* curComponent : components)
	{
		if (isBeingDeleted()) return;
		curComponent->start();
	}
}

void GameObject::update()
{
	if (isBeingDeleted()) return;
	for (Component* curComponent : components)
	{
		if (isBeingDeleted()) return;
		curComponent->update();
	}
}

void GameObject::lateUpdate()
{
	if (isBeingDeleted()) return;
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
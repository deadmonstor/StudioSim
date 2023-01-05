#include "GameObject.h"
#include "Component.h"

GameObject::GameObject()
{
	
}

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
	// TODO: Make sure start is called after prefab creation or its gonna suck
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

void GameObject::render()
{
	for (Component* curComponent : components)
	{
		curComponent->render();
	}
}

void GameObject::addComponent(Component* component)
{
	components.push_back(component);
}

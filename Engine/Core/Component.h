#pragma once
#include <string>

class GameObject;

class Component
{
	GameObject* owner = nullptr;
	std::string name;
public:
	virtual ~Component() = 0;

	virtual void start();
	virtual void update();
	virtual void lateUpdate();
	virtual void getDebugInfo(std::string*);

	void setOwner(GameObject* owner) { this->owner = owner; }
	GameObject* getOwner() const { return owner; }

	void setName(const std::string name) { this->name = name; }
	std::string getName() const { return name; }
};
#pragma once
#include <string>

class GameObject;

class Component
{
public:
	std::string name;
	
	GameObject* owner;
	virtual ~Component() = 0;

	virtual void start();
	virtual void update();
	virtual void lateUpdate();
	virtual void getDebugInfo(std::string*);
};
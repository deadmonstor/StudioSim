#pragma once

class Component
{
	// TODO: probably needs a type? typeid()
	
public:
	virtual ~Component() = 0;

	virtual void start();
	virtual void update();
	virtual void lateUpdate();
	virtual void render();
};

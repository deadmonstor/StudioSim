#include "Component.h"
#include "Core/GameObject.h"

void Component::start()
{
	
}

void Component::update()
{
	
}

void Component::lateUpdate()
{
	
}

void Component::destroy()
{
	
}

void Component::getDebugInfo(std::string*)
{

}

Component::~Component()
{
	this->owner = nullptr;
}

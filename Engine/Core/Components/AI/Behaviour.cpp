#include "Behaviour.h"

Behaviour::Behaviour()
{
	initialised = false;
	entered = false;
}

Behaviour::~Behaviour() 
{ 
	CleanUp(); 
	Component::~Component();
}

void Behaviour::Entry() 
{
	if (!initialised) 
	{
		start();
	}
}

void Behaviour::Exit() {}

void Behaviour::Act() {}

void Behaviour::start() 
{ 
	initialised = true; 
}

Behaviour *Behaviour::FindTransition(const FSMTransition transitionEvent) 
{ 
	//continue development here....
	return nullptr; 
}

void Behaviour::CleanUp() 
{

}

#include "Light.h"

#include "Util/Events/EngineEvents.h"
#include "Util/Events/Events.h"

Light::~Light()
{
	Griddy::Events::invoke<OnLightComponentRemoved>(this);
}

void Light::start()
{
	Component::start();
	Griddy::Events::invoke<OnLightComponentStarted>(this);
}
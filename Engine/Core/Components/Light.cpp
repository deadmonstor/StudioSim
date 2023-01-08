#include "Light.h"

#include "Core/GameObject.h"
#include "Core/Renderer/Lighting.h"
#include "Util/Events/RenderEvents.h"
#include "Util/Events/Events.h"

Light::~Light()
{
	Component::~Component();
	Griddy::Events::invoke<OnLightComponentRemoved>(this);
}

void Light::setColor(const glm::vec4& _color)
{
	this->color = _color;
	Lighting::Instance()->refreshLightData(LightUpdateRequest::Color);
}

void Light::setFalloff(const glm::vec3& _falloff)
{
	this->falloff = _falloff;
	Lighting::Instance()->refreshLightData(LightUpdateRequest::Falloff);
}

void Light::start()
{
	Component::start();
	Griddy::Events::invoke<OnLightComponentStarted>(this);
}

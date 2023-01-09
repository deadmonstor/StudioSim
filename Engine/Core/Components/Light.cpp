#include "Light.h"

#include "Core/GameObject.h"
#include "Core/Renderer/Lighting.h"
#include "Util/Events/RenderEvents.h"
#include "Util/Events/Events.h"

void Light::start()
{
	Component::start();
	Griddy::Events::invoke<OnLightComponentStarted>(this);
}

Light::~Light()
{
	Component::~Component();
	Griddy::Events::invoke<OnLightComponentRemoved>(this);
}

void Light::getDebugInfo(std::string* string)
{
	std::stringstream ss;
	ss << "Color: " << color.x << ", " << color.y << ", " << color.z << std::endl;
	ss << "Falloff: " << falloff.x << ", " << falloff.y << ", " << falloff.z << std::endl;
	string->append(ss.str());
	Component::getDebugInfo(string);
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


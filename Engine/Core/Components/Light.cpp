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
	ImGui::Indent();
	ImGui::TextUnformatted("Color: ");
	const auto internalColor = new float[4]{ this->color.r, this->color.g, this->color.b, this->color.a };
	ImGui::ColorEdit4("", internalColor);

	ImGui::TextUnformatted("Falloff: ");
	const auto internalFloat = new float[3]{ this->falloff.x, this->falloff.y, this->falloff.z };
	ImGui::DragFloat3("", internalFloat);
	ImGui::Unindent();

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


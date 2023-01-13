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

void Light::destroy()
{
	Component::destroy();
	Griddy::Events::invoke<OnLightComponentRemoved>(this);
}

void Light::getDebugInfo(std::string* string)
{
	ImGui::Indent();
	ImGui::ColorEdit4("Color", debugColor);

	if (abs(debugColor[0] - color.r) > 0.01f ||
		abs(debugColor[1] - color.g) > 0.01f ||
		abs(debugColor[2] - color.b) > 0.01f ||
		abs(debugColor[3] - color.a) > 0.01f)
	{
		setColor(glm::vec4(debugColor[0], debugColor[1], debugColor[2], debugColor[3]));
	}
	
	ImGui::DragFloat3("Falloff", debugFalloff);

	if (abs(debugFalloff[0] - falloff.x) > 0.01f ||
		abs(debugFalloff[1] - falloff.y) > 0.01f ||
		abs(debugFalloff[2] - falloff.z) > 0.01f)
	{
		setFalloff(glm::vec3(debugFalloff[0], debugFalloff[1], debugFalloff[2]));
	}
	
	ImGui::Unindent();

	Component::getDebugInfo(string);
}

void Light::setColor(const glm::vec4& _color)
{
	this->color = _color;
	
	this->debugColor[0] = this->color.r;
	this->debugColor[1] = this->color.g;
	this->debugColor[2] = this->color.b;
	this->debugColor[3] = this->color.a;
	
	Lighting::Instance()->refreshLightData(LightUpdateRequest::Color);
}

void Light::setFalloff(const glm::vec3& _falloff)
{
	this->falloff = _falloff;
	
	this->debugFalloff[0] = this->falloff.r;
	this->debugFalloff[1] = this->falloff.g;
	this->debugFalloff[2] = this->falloff.b;
	
	Lighting::Instance()->refreshLightData(LightUpdateRequest::Falloff);
}


#include "Transform.h"

#include <sstream>

#include "Core/GameObject.h"
#include "Core/Renderer/Renderer.h"

void Transform::getDebugInfo(std::string* string)
{
	ImGui::Indent();
	ImGui::DragFloat2("Position", debugPosition);

	if (abs(debugPosition[0] - position.x) > 0.01f || abs(debugPosition[1] - position.y) > 0.01f)
	{
		setPosition({debugPosition[0], debugPosition[1]});
	}
	
	ImGui::DragFloat("Rotation", &debugRotation);

	if (abs(debugRotation - rotation) > 0.01f)
	{
		setRotation(debugRotation);
	}
	
	ImGui::DragFloat2("Size", debugSize);

	if (abs(debugSize[0] - size.x) > 0.01f || abs(debugSize[1] - size.y) > 0.01f)
	{
		setSize({debugSize[0], debugSize[1]});
	}
	
	ImGui::Unindent();

	Component::getDebugInfo(string);
}

glm::vec2 Transform::getPosition() const
{
	const glm::vec2 camPos = Renderer::Instance()->getCameraPos();
	return position - camPos;
}

void Transform::setPosition(const glm::vec2 inPosition)
{
	const glm::vec2 camPos = Renderer::Instance()->getCameraPos();
	this->position = inPosition + camPos;

	debugPosition[0] = inPosition.x;
	debugPosition[1] = inPosition.y;
}

void Transform::setRotation(const float inRotation)
{
	this->rotation = inRotation;

	debugRotation = inRotation;
}

void Transform::destroy()
{
	
}

void Transform::setSize(const glm::vec2 inScale)
{
	this->size = inScale;

	debugSize[0] = inScale.x;
	debugSize[1] = inScale.y;
}

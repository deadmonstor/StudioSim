#include "Transform.h"

#include <sstream>

#include "Core/GameObject.h"
#include "Core/Renderer/Renderer.h"

void Transform::getDebugInfo(std::string* string)
{
	std::stringstream ss;
	ss << "Position: " << position.x << ", " << position.y << std::endl;
	ss << "Rotation: " << rotation << std::endl;
	ss << "Size: " << size.x << ", " << size.y << std::endl;
	string->append(ss.str());
}

glm::vec2 Transform::GetPosition() const
{
	const glm::vec2 camPos = Renderer::Instance()->GetCameraPos();
	return position - camPos;
}

void Transform::SetPosition(const glm::vec2 inPosition)
{
	const glm::vec2 camPos = Renderer::Instance()->GetCameraPos();
	this->position = inPosition + camPos;
}

void Transform::SetRotation(const float inRotation)
{
	this->rotation = inRotation;
}

void Transform::SetScale(const glm::vec2 inScale)
{
	this->size = inScale;
}

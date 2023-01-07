#include "Transform.h"

#include <sstream>

void Transform::getDebugInfo(std::string* string)
{
	std::stringstream ss;
	ss << "Position: " << position.x << ", " << position.y << std::endl;
	ss << "Rotation: " << rotation << std::endl;
	ss << "Size: " << size.x << ", " << size.y << std::endl;
	string->append(ss.str());
}

void Transform::SetPosition(const glm::vec2 inPosition)
{
	this->position = inPosition;
}

void Transform::SetRotation(const float inRotation)
{
	this->rotation = inRotation;
}

void Transform::SetScale(const glm::vec2 inScale)
{
	this->size = inScale;
}

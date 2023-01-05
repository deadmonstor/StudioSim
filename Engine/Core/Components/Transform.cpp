#include "Transform.h"

Transform::~Transform() = default;

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
	this->scale = inScale;
}

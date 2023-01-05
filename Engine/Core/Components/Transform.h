#pragma once
#include "../Component.h"
#include "glm/vec2.hpp"

class Transform : public Component
{
	glm::vec2 position = { 0, 0};
	glm::vec2 scale = {0, 0};
	float rotation = 0;
	
public:
	~Transform() override {}

	void SetPosition(glm::vec2 inPosition);
	void SetScale(glm::vec2 inScale);
	void SetRotation(float inRotation);

	glm::vec2 GetPosition() const { return position; }
	glm::vec2 GetScale() const { return scale; }
	float GetRotation() const { return rotation; }
};

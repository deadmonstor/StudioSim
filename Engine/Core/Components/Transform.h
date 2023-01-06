#pragma once
#include "../Component.h"
#include "glm/vec2.hpp"

class Transform final : public Component
{
	glm::vec2 position = { 0, 0};
	glm::vec2 scale = {100, 100};
	float rotation = 0;
	
public:
	void SetPosition(glm::vec2 inPosition);
	void SetScale(glm::vec2 inScale);
	void SetRotation(float inRotation);

	[[nodiscard]] glm::vec2 GetPosition() const { return position; }
	[[nodiscard]] glm::vec2 GetScale() const { return scale; }
	[[nodiscard]] float GetRotation() const { return rotation; }
};

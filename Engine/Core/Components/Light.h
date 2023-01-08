#pragma once
#include "Core/Component.h"
#include "glm/vec4.hpp"

class Light final : public Component
{
public:
	void start() override;
	~Light() override;

	glm::vec4 getColor() const { return color; }
	void setColor(const glm::vec4 color) { this->color = color; }
private:
	glm::vec4 color = glm::vec4 {1.0f, 0.75f, 0.3f, 1.0f};
};

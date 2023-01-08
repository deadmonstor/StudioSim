#pragma once
#include "Core/Component.h"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

class Light final : public Component
{
public:
	void start() override;
	~Light() override;

	glm::vec4 getColor() const { return color; }
	void setColor(const glm::vec4& _color) { this->color = _color; }
	
	glm::vec3 getFalloff() const { return falloff; }
	void setFalloff(const glm::vec3& _falloff) { this->falloff = _falloff; }
private:
	glm::vec4 color = glm::vec4 {1.0f, 0.75f, 0.3f, 1.0f};
	glm::vec3 falloff = glm::vec3 {0.4f, 3.0f, 20.0f};
};

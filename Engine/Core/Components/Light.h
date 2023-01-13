#pragma once
#include "Core/Component.h"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

class Light final : public Component
{
public:
	void start() override;
	void destroy() override;

	void getDebugInfo(std::string*) override;

	glm::vec4 getColor() const { return color; }
	void setColor(const glm::vec4& _color);

	glm::vec3 getFalloff() const { return falloff; }
	void setFalloff(const glm::vec3& _falloff);
private:
	glm::vec4 color = glm::vec4 {1.0f, 0.75f, 0.3f, 1.0f};
	glm::vec3 falloff = glm::vec3 {1.0f, 4.0f, 25.0f};

	float debugColor[4] = {1.0f, 0.75f, 0.3f, 1.0f};
	float debugFalloff[3] = {1.0f, 4.0f, 25.0f};
};

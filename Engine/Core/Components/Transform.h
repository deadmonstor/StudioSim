#pragma once
#include "../Component.h"
#include "glm/vec2.hpp"

class Transform final : public Component
{
	friend class Renderer;
	
	glm::vec2 position = { 0, 0};
	glm::vec2 size = {1, 1};
	float rotation = 0;

	float debugPosition[2] = {0, 0};
	float debugSize[2] = {1, 1};
	float debugRotation = 0;
	
public:
	void getDebugInfo(std::string*) override;
	void setPosition(glm::vec2 inPosition);
	void setSize(glm::vec2 inScale);
	void setRotation(float inRotation);
	void destroy() override;

	[[nodiscard]] glm::vec2 getPosition() const;
	[[nodiscard]] glm::vec2 GetScale() const { return size; }
	[[nodiscard]] float GetRotation() const { return rotation; }
};

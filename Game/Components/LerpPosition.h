#pragma once 

#include <functional>
#include "Core/Component.h"
#include "glm/vec2.hpp"

class LerpPosition final : public Component
{
	glm::vec2 targetPosition = {0, 0};
	glm::vec2 startPosition  = {0, 0};
	bool hasFinished = true;
	float internalTimer = 0.0f;
	float speed = 1.0f;
	
public:
	explicit LerpPosition(glm::vec2 _targetPosition, float _speed);
	
	void start() override;
	void update() override;
	void destroy() override;

	void setPosition(const glm::vec2& position);
	void setSpeed(const float _speed) { speed = _speed; }
	
	std::function<void()> onLerpComplete;
};

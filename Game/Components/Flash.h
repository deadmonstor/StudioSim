#pragma once 

#include "Core/Component.h"
#include "Core/Components/SpriteComponent.h"
#include "glm/vec3.hpp"

class Flash final : public Component
{
	glm::vec3 targetColor = {0, 0, 0};
	glm::vec3 startColor  = {0, 0, 0};

	SpriteComponent* spriteComponent = nullptr;
	
	bool hasFinished = true;
	float internalTimer = 0.0f;
	float speed = 1.0f;
	
public:
	explicit Flash(SpriteComponent* _spriteComponent, glm::vec3 _targetColor, float _speed);
	
	void start() override;
	void update() override;
	void destroy() override;

	void setColor(const glm::vec3& _color);
	void setSpeed(const float _speed) { speed = _speed; }
	std::function<void()> onFlashComplete;
};

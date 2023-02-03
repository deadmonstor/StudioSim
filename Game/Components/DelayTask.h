#pragma once 

#include <functional>
#include "Core/Component.h"

class DelayTask final : public Component
{
	bool hasFinished = true;
	float internalTimer = 0.0f;
	float speed = 1.0f;
	
public:
	explicit DelayTask(int speed, const std::function<void()>& _onComplete);
	
	void start() override;
	void update() override;
	void destroy() override;
	static void createTask(GameObject* object, float speed, const std::function<void()>& _onComplete);

	void setSpeed(float speed) { this->speed = speed;}
	
	std::function<void()> onComplete;
};

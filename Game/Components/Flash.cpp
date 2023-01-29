#include "Flash.h"

#include "Core/GameObject.h"
#include "Core/Components/SpriteComponent.h"
#include "Core/Components/Transform.h"
#include "glm/gtx/compatibility.hpp"
#include "Util/Time.h"

Flash::Flash(SpriteComponent* _spriteComponent, const glm::vec3 _color, const float _speed)
{
	spriteComponent = _spriteComponent;
	targetColor = _color;
	speed = _speed;
}

void Flash::start()
{
	setColor(targetColor);
}

void Flash::update()
{
	if (hasFinished)
		return;

	internalTimer += static_cast<float>(Time::getDeltaTime()) * speed;
	internalTimer = glm::clamp(internalTimer, 0.0f, 1.0f);
	
	if (internalTimer == 1.0f)
	{
		hasFinished = true;
		spriteComponent->setColor(startColor);
		onFlashComplete();
	}
	else
	{
		spriteComponent->setColor(targetColor);
	}
}

void Flash::destroy()
{

}

void Flash::setColor(const glm::vec3& _color)
{
	startColor = spriteComponent->getColor();
	targetColor = _color;
	hasFinished = false;
	internalTimer = 0.0f;
}

#include "LerpPosition.h"

#include "Core/GameObject.h"
#include "Core/Components/Transform.h"
#include "glm/geometric.hpp"
#include "glm/gtx/compatibility.hpp"
#include "Util/Time.h"

LerpPosition::LerpPosition(const glm::vec2 _targetPosition, const float _speed)
{
	targetPosition = _targetPosition;
	speed = _speed;
}

void LerpPosition::start()
{
	setPosition(targetPosition);
}

void LerpPosition::update()
{
	if (hasFinished)
		return;

	internalTimer += static_cast<float>(Time::getDeltaTime()) * speed;
	internalTimer = glm::clamp(internalTimer, 0.0f, 1.0f);
	
	if (glm::distance(getOwner()->getTransform()->getPosition(), targetPosition) > 0.1f)
	{
		getOwner()->getTransform()->setPosition(
			lerp(startPosition, targetPosition, internalTimer));
	}
	else
	{
		onLerpComplete();
		hasFinished = true;
	}
}

void LerpPosition::destroy()
{

}

void LerpPosition::setPosition(const glm::vec2& position)
{
	startPosition = getOwner()->getTransform()->getPosition();
	targetPosition = position;
	hasFinished = false;
	internalTimer = 0.0f;
}

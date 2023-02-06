#include "Health.h"

#include "Transform.h"
#include "../../../Game/Components/Hitmarkers.h"
#include "../../../Game/Components/Player/PlayerController.h"
#include "Core/SceneManager.h"

void Health::setHealth(const float healthToSet)
{
	const float difference = healthToSet - currentHealth;
	currentHealth = healthToSet;

	if (currentHealth <= 0)
	{
		die();
		PlayerController::Instance()->hitmarkers->addHitmarker("DIED!", 1.0, getOwner()->getTransform()->getPosition());
	}
	else
	{
		PlayerController::Instance()->hitmarkers->addHitmarker(std::format("{:.0f}", difference), 1.0, getOwner()->getTransform()->getPosition());
	}
}

void Health::die()
{
	SceneManager::Instance()->destroyGameObject(getOwner());
}
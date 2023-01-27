#include "Health.h"

#include "Core/SceneManager.h"

void Health::setHealth(const float healthToSet)
{
	currentHealth = healthToSet;

	if (currentHealth <= 0)
	{
		die();
	}
}

void Health::die()
{
	SceneManager::Instance()->destroyGameObject(getOwner());
}
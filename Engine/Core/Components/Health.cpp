#include "Health.h"

#include "Transform.h"
#include "../../../Game/Components/Hitmarkers.h"
#include "Core/SceneManager.h"

void Health::setHealth(const float healthToSet)
{
	const float difference = healthToSet - currentHealth;
	if (!getOwner()->hasComponent(typeid(Hitmarkers)))
		getOwner()->addComponent<Hitmarkers>();
	
	//currentHealth = healthToSet;

	if (currentHealth <= 0)
	{
		//die();
		getOwner()->getComponent<Hitmarkers>()->addHitmarker("DIED!", 1.0, getOwner()->getTransform()->getPosition());
	}
	else
	{
		getOwner()->getComponent<Hitmarkers>()->addHitmarker(std::format("{:.0f}", difference), 1.0, getOwner()->getTransform()->getPosition());
	}
}

void Health::die()
{
	SceneManager::Instance()->destroyGameObject(getOwner());
}
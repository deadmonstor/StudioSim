#pragma once
#include "Core/Component.h"

class Health : public Component
{
public:
	float currentHealth;
	void setHealth(float healthToSet) { currentHealth = healthToSet; }
	float getHealth() { return currentHealth; }
};

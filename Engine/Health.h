#pragma once
#include "Core/Component.h"

class Health : public Component
{
public:
	void setHealth(float healthToSet) { currentHealth = healthToSet; }
	float getHealth() { return currentHealth; }

private:
	float currentHealth;
};

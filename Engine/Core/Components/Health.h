#pragma once
#include "Core/Component.h"

class Health : public Component
{
public:
	float getHealth() const { return currentHealth; }
	void setHealth(float healthToSet);
	void die();

private:
	float currentHealth = 100;
};

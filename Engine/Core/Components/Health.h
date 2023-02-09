#pragma once
#include "Core/Component.h"

class Health : public Component
{
public:
	explicit Health(int healthArg) : currentHealth(healthArg) {}
	float getHealth() const { return currentHealth; }
	void setHealth(float healthToSet);
	void die();

private:
	float currentHealth = -1;
};

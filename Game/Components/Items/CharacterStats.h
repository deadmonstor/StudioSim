#pragma once
struct Character
{
	int currentHealth;
	int getCurrentHealth() { return currentHealth; }

	int maxHealth;
	int getMaxHealth() { return maxHealth; }
	void setMaxHealth(int mHealth) { mHealth = maxHealth; }


	int attack;
	int defence;

	float critChance;

};
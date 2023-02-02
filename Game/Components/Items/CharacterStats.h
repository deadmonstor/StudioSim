#pragma once
struct character
{
	int currentHealth;
	int maxHealth;

	int attack;
	int defence;

	float critChance;

	virtual void TakeDamage(int damage) 
	{
		/* 
		currentHealth = cH - (atk - (D*2));

		in case of critChance 
		currentHealth = cH - (atk * 2);

		if (atk - (D*2) <=0)
		atk - (D*2) = 1
		*/
	};
};
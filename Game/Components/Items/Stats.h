#pragma once
#include "CharacterStats.h"
#include "ItemStats.h"
#include <iostream>
#include <string>

struct PlayerStats : public Character
{
	Character character;
	PlayerStats() 
	{
		character.currentHealth;
	}
	//int strength = currentHealth +;
	//if (strength <= 1) strength = 1;
	/*int getStrength() { return strength; };*/



	int currentMana;
	int getCurrentMana() { return currentMana; }

	int maxMana;
	int getMaxMana() { return maxMana; }

	int coinsHeld;
	int getCoinsHeld() { return coinsHeld; }

	int currentEXP;
	int getCurrentEXP() { return currentEXP; }

	int maxEXP;
	int getMaxExp() { return maxEXP; }

	int spellPower;
	int getSpellPower() { return spellPower; }


};

struct EnemyStats : public Character
{
	int EXPDropped;
};

struct ArmourStats : public Item
{ 
	int defence;
	int costInShop;
	int mana;
	int health;
};

struct WeaponStats : public Item
{
	int attack;
	int costInShop;
};

struct ConsumableStats : public Item
{
	int healthGained;
	int manaGained;
	int EXPGained;
	int costInShop;
};

struct SpellsStats : public Item
{
	int manaCost;
	int getManaCost() { return manaCost; }

	int spellDamage;
	int getSpellDamage() { return spellDamage; }

	int cooldown;
	int getCoolDown() { return cooldown; }

	int range;
	int getRange() { return range; }

	int damagePerTurn;
	int getDamagePerTurn() { return damagePerTurn; }
	
};

struct LootTables : public Item
{
	std::string itemName;
	float dropChance;
};
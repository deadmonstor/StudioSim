#pragma once
#include "CharacterStats.h"
#include "ItemStats.h"
#include <iostream>
#include <string>

class Inventory;

struct PlayerStats : public character
{
	int currentMana;
	int maxMana;
	int coinsHeld;
	int currentEXP;
	int maxEXP;
	int spellPower;
	int level;

	Inventory* myInventory;
};

struct EnemyStats : public character
{
	int EXPDropped;
};

struct ArmourStats : public items
{ 
	int defence;
	int health;
	int mana;
	int costInShop;
};

struct WeaponStats : public items
{
	int attack;
	int costInShop;
};

struct ConsumableStats : public items
{
	int healthGained;
	int manaGained;
	int EXPGained;
	int costInShop;
};

struct SpellsStats : public items
{
	int manaCost;
	int spellPower;
	int currentCooldown;
	int maxCooldown;
	int range;
	int damagePerTurn;
};

struct LootTables : public items
{
	std::string itemName;
	float dropChance;
};
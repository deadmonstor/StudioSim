#pragma once
#include "CharacterStats.h"
#include "ItemStats.h"
#include <iostream>
#include <string>

class Inventory;

struct PlayerStats : public Character
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

struct EnemyStats : public Character
{
	int EXPDropped;
};

struct ArmourStats : public ItemInfo
{ 
	int defence;
	int health;
	int mana;
};

struct WeaponStats : public ItemInfo
{
	int attack;
	int costInShop;
	int crit = 2;
};

struct ConsumableStats : public ItemInfo
{
	int healthGained;
	int manaGained;
	int EXPGained;
};

struct SpellsStats : public ItemInfo
{
	int manaCost;
	int spellPower;
	int currentCooldown;
	int maxCooldown;
	int range;
	int damagePerTurn;
};

struct LootTables : public ItemInfo
{
	std::string itemName;
	float dropChance;
};
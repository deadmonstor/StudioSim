#pragma once
#include "CharacterStats.h"
#include "ItemStats.h"
#include <iostream>
#include <string>

//struct PlayerStats : public Character
//{
//	int currentMana;
//	int maxMana;
//	int coinsHeld;
//	int currentEXP;
//	int maxEXP;
//	int spellPower;
//};

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
	int cooldown;
	int range;
	int damagePerTurn;
	int spellCooldown;
	
};

struct LootTables : public ItemInfo
{
	std::string itemName;
	float dropChance;
};
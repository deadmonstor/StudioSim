#pragma once
#include "StatSystem.h"

struct PlayerStats : public StatSystem
{
	int coinsHeld;
};

struct ArmourStats : public StatSystem
{

};

struct WeaponStats : public StatSystem
{

};

struct ConsumableStats : public StatSystem
{

};

struct SpellsStats : public StatSystem
{
	int manaCost;
	int cooldown;
	int spellPower;
	int range;
	int turnsEffected;
	int dmgPerTurn;
};
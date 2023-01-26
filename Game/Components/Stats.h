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
	int spellCooldown;
};
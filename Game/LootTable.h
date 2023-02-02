#pragma once
#include "Core/Component.h"
#include "Util/SingletonTemplate.h"
#include<string>
#include <fstream>

struct LootTableData
{
	std::string ItemName;
	float DropChance;
};

class LootTable : public SingletonTemplate<LootTable>
{
public:
	void LoadingIntoLootTableArray();
	std::string RollLoot();

private:

	std::fstream file;

	LootTableData m_LootTableData[9];
};


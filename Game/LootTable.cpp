#include "LootTable.h"
#include <iostream>

void LootTable::LoadingIntoLootTableArray()
{
	file.open("LootTable.txt");
	std::string line, m_Name;
	size_t pos = 0;
	std::string delim = "-";

	for (int i = 0; i < 11 && std::getline(file, line); i++)
	{
		while ((pos = line.find(delim)) != std::string::npos)
		{
			m_Name = line.substr(0, pos);
			m_LootTableData[i].ItemName = m_Name;
			line.erase(0, pos + delim.length());
			m_LootTableData[i].DropChance = std::stoi(line);
		}
	}
	
	RollLoot();
}

std::string LootTable::RollLoot()
{
	
	//Roll random number 0-100. rand % 100
	srand(time(0));

	const float random = (rand() % 100) + 1;
	float temp = 0;
	for (const auto& [ItemName, DropChance] : m_LootTableData)
	{
		temp += DropChance;
		if (random < temp)
		{
			return ItemName;
		}
	}
	
}

void EnemyDropLootTable::EnemyDropLoadingIntoLootTableArray()
{
	file.open("EnemyDropLootTable.txt");
	std::string line;
	size_t pos;
	const std::string delim = "-";

	for (int i = 0; i < 11 && std::getline(file, line); i++)
	{
		while ((pos = line.find(delim)) != std::string::npos)
		{
			std::string m_Name = line.substr(0, pos);
			m_EnemyDropLootTableData[i].ItemName = m_Name;
			line.erase(0, pos + delim.length());
			m_EnemyDropLootTableData[i].DropChance = std::stoi(line);
		}
	}
	
	EnemyDropRollLoot();
}

std::string EnemyDropLootTable::EnemyDropRollLoot()
{
	//Roll random number 0-100. rand % 100
	srand(time(0));

	//random number
	const float random = (rand() % 100) + 1;
	float temp = 0;
	for (const auto& [ItemName, DropChance] : m_EnemyDropLootTableData)
	{
		temp += DropChance;
		if (random < temp)
		{
			std::string rolledLoot = ItemName;
			if (ItemName == "money")
			{
				int random = (rand() % 16) +1;
				rolledLoot.append("," + std::to_string(random));
				std::cout << rolledLoot;
			}
			
			return rolledLoot;
		}
	}

}

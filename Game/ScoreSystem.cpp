#include "ScoreSystem.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Core/Components/TextRenderer.h"

ScoreSystem::ScoreSystem()
{
	currentScore = 0;
}

void ScoreSystem::SaveScore(std::string Username)
{

	file.open("Score.txt", std::ios::app);
	if (file)
	{
		file << Username << "-" << currentScore << "\n";
		file.close();

	}
	else
	{
		std::cout << "File Doesn't Exist";
		file.open("Score.txt", std::ios::out);
		file << Username << "-" << currentScore << "\n";
		file.close();
	}


}

void ScoreSystem::ReadScores(bool FromMainMenu)
{
	file.open("Score.txt");
	std::string line, m_Name;
	size_t pos = 0;
	std::string delim = "-";

	for (int i = 0; i < 11 && std::getline(file, line); i++)
	{
		while ((pos = line.find(delim)) != std::string::npos)
		{
			m_Name = line.substr(0, pos);
			m_FileData[i].Name = m_Name;
			line.erase(0, pos + delim.length());
			m_FileData[i].Score = std::stoi(line);
		}
	}
	file.close();
	if (!FromMainMenu)
	{
		SortScores();
		UpdateScoreFile();
	}
}

void ScoreSystem::SortScores()
{
	for (int i = 11; i > 0; i--)
	{
		if (m_FileData[i].Score > m_FileData[i-1].Score)
		{
			m_FileData[12] = m_FileData[i - 1];
			m_FileData[i - 1] = m_FileData[i];
			m_FileData[i] = m_FileData[12];
		}
		
	}
	m_FileData[12].Score = NULL;
}

void ScoreSystem::UpdateScoreFile()
{
	file.open("Score.txt", std::ios::out);
	for (int i = 0; m_FileData[i].Score != NULL && i < 10; i++)
	{
		
		file << m_FileData[i].Name << "-" << m_FileData[i].Score << "\n";
		
	}
	file.close();
	
}

void ScoreSystem::RenderTopScores()
{
	for (int i = 0; i < 10; i++)
	{
		TextRenderer::Instance()->renderText(m_FileData[i].Name, 200, i * 100 - 300, 1, glm::vec3(1, 1, 1));
		TextRenderer::Instance()->renderText(std::to_string(m_FileData[i].Score), 500, i * 100 - 300, 1, glm::vec3(1, 1, 1));
	}
	//TextRenderer::Instance()->renderText("", 500, 500, 1, glm::vec3(1, 1, 1));
}
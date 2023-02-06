#include "ScoreSystem.h"
#include <iostream>
#include <fstream>
#include <algorithm>

#include "Core/Pivot.h"
#include "Core/Components/TextRenderer.h"
#include "Core/Renderer/Renderer.h"

ScoreSystem::ScoreSystem()
{
	currentScore = 0;
	damageTaken = 0;
	enemiesKilled = 0;
	tilesMoved = 0;
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

void ScoreSystem::calcFinalScore()
{
	currentScore += enemiesKilled * 10;
	currentScore += tilesMoved * 10;
	currentScore -= damageTaken * 10;
}

void ScoreSystem::RenderTopScores()
{
	const auto MiddleTop =
		glm::vec2((Renderer::getWindowSize().x / 2), (Renderer::getWindowSize().y)) / Renderer::Instance()->getAspectRatio();

	//Offsets for Scores
	int offsetY = 40;
	int offsetX = -40;

	glm::vec2 sizeOfText = TextRenderer::Instance()->renderTextSize("The Leaderboard:", 1);
	TextRenderer::Instance()->renderText("The Leaderboard:", MiddleTop.x - (sizeOfText.x / 2),
		MiddleTop.y - (sizeOfText.y / 2) - 50, 1, glm::vec3{ 1, 1, 1 }, glm::vec2{ 0, 0 });

	for (int i = 0; i < 10; i++)
	{
		sizeOfText = TextRenderer::Instance()->renderTextSize(m_FileData[9 - i].Name, 0.6);
		TextRenderer::Instance()->renderText(m_FileData[i].Name, MiddleTop.x - (sizeOfText.x / 2) - 110,
			MiddleTop.y - (sizeOfText.y / 2) - (i * offsetY) - offsetY - 60, 0.6, glm::vec3(1, 1, 1), Pivot::BottomLeft);

		sizeOfText = TextRenderer::Instance()->renderTextSize(std::to_string(m_FileData[9 - i].Score), 0.6);
		TextRenderer::Instance()->renderText(std::to_string(m_FileData[i].Score), MiddleTop.x - (sizeOfText.x / 2) + offsetX,
			MiddleTop.y - (sizeOfText.y / 2) - (i * offsetY) - offsetY - 60, 0.6, glm::vec3(1, 1, 1),  Pivot::BottomLeft);
	}
	//TextRenderer::Instance()->renderText("", 500, 500, 1, glm::vec3(1, 1, 1));
}
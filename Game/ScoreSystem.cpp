#include "ScoreSystem.h"
#include <iostream>
#include <fstream>
#include <algorithm>

#include "Core/Pivot.h"
#include "Core/Components/TextRenderer.h"
#include "Core/Renderer/Renderer.h"

ScoreSystem::ScoreSystem()
{
	resetScoreSystem();
}

void ScoreSystem::resetScoreSystem()
{
	currentScore = 0;
	damageTaken = 0;
	enemiesKilled = 0;
	tilesMoved = 0;
	goldEarned = 0;
}

void ScoreSystem::SaveScore(std::string Username)
{
	file.open("Score.txt", std::ios::app);
	if (file)
	{
		file << Username << "," << currentScore << "\n";
		file.close();
	}
	else
	{
		std::cout << "File Doesn't Exist";
		file.open("Score.txt", std::ios::out);
		file << Username << "," << currentScore << "\n";
		file.close();
	}
}

void ScoreSystem::ReadScores(bool FromMainMenu)
{
	file.open("Score.txt");
	std::string line, m_Name;
	size_t pos = 0;
	std::string delim = ",";

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
		
		file << m_FileData[i].Name << "," << m_FileData[i].Score << "\n";
		
	}
	file.close();
	
}

void ScoreSystem::calcFinalScore()
{
	currentScore = 0;
	currentScore += enemiesKilled * 10;
	currentScore += tilesMoved;
	currentScore += goldEarned;
	currentScore -= damageTaken;
}

void ScoreSystem::RenderTopScores()
{
	const auto MiddleTop =
					glm::vec2((Renderer::getViewportSize().x / 3), Renderer::getViewportSize().y);

	glm::vec2 sizeOfText = TextRenderer::Instance()->renderTextSize("The Leaderboard:", 1);
	TextRenderer::Instance()->renderText("The Leaderboard:",
		MiddleTop.x - (sizeOfText.x / 2),
		MiddleTop.y - (sizeOfText.y / 2) - 50,
		1,
		glm::vec3{ 1, 1, 1 },
		glm::vec2{ 0, 0 });

	for (int i = 0; i < 10; i++)
	{
		constexpr float offsetY = 40;
		
		sizeOfText = TextRenderer::Instance()->renderTextSize(m_FileData[i].Name + ": " + std::to_string(m_FileData[i].Score), 0.6f);
		TextRenderer::Instance()->renderText(m_FileData[i].Name + ": " + std::to_string(m_FileData[i].Score),
			MiddleTop.x - (sizeOfText.x / 2),
			MiddleTop.y - (sizeOfText.y / 2) - (i * offsetY) - offsetY - 60,
			0.6f,
			glm::vec3(1, 1, 1),
			Pivot::BottomLeft);
	}

	auto TopRight =
		glm::vec2(Renderer::getViewportSize().x / 1.5f, Renderer::getViewportSize().y);

	sizeOfText = TextRenderer::Instance()->renderTextSize("Your Score:", 1);
	TextRenderer::Instance()->renderText("Your Score:",
		TopRight.x - (sizeOfText.x / 2),
		TopRight.y - (sizeOfText.y / 2) - 50,
		1,
		glm::vec3{ 1, 1, 1 },
		glm::vec2{ 0, 0 });

	TopRight.y -= 75;
	
	sizeOfText = TextRenderer::Instance()->renderTextSize("Enemies Killed: " + std::to_string(enemiesKilled), 0.6f);
	TextRenderer::Instance()->renderText("Enemies Killed: " + std::to_string(enemiesKilled),
		TopRight.x - (sizeOfText.x / 2),
		TopRight.y - (sizeOfText.y / 2) - 50,
		0.6f,
		glm::vec3{ 1, 1, 1 },
		glm::vec2{ 0, 0 });

	TopRight.y -= 50;
	
	sizeOfText = TextRenderer::Instance()->renderTextSize("Tiles Moved: " + std::to_string(tilesMoved), 0.6f);
	TextRenderer::Instance()->renderText("Tiles Moved: " + std::to_string(tilesMoved),
		TopRight.x - (sizeOfText.x / 2),
		TopRight.y - (sizeOfText.y / 2) - 50,
		0.6f,
		glm::vec3{ 1, 1, 1 },
		glm::vec2{ 0, 0 });

	TopRight.y -= 50;
	
	sizeOfText = TextRenderer::Instance()->renderTextSize("Damage Taken: " + std::to_string(damageTaken), 0.6f);
	TextRenderer::Instance()->renderText("Damage Taken: " + std::to_string(damageTaken),
		TopRight.x - (sizeOfText.x / 2),
		TopRight.y - (sizeOfText.y / 2) - 50,
		0.6f,
		glm::vec3{ 1, 1, 1 },
		glm::vec2{ 0, 0 });

	TopRight.y -= 50;
	
	sizeOfText = TextRenderer::Instance()->renderTextSize("Gold Earned: " + std::to_string(goldEarned), 0.6f);
	TextRenderer::Instance()->renderText("Gold Earned: " + std::to_string(goldEarned),
		TopRight.x - (sizeOfText.x / 2),
		TopRight.y - (sizeOfText.y / 2) - 50,
		0.6f,
		glm::vec3{ 1, 1, 1 },
		glm::vec2{ 0, 0 });
	
	TopRight.y -= 75;
	calcFinalScore();
	
	sizeOfText = TextRenderer::Instance()->renderTextSize("Total Score: " + std::to_string(currentScore), 1);
	TextRenderer::Instance()->renderText("Total Score: " + std::to_string(currentScore),
		TopRight.x - (sizeOfText.x / 2),
		TopRight.y - (sizeOfText.y / 2) - 50,
		1,
		glm::vec3{ 1, 1, 1 },
		glm::vec2{ 0, 0 });
}
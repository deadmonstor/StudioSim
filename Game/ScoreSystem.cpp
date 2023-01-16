#include "ScoreSystem.h"
#include <iostream>
#include <fstream>
#include <algorithm>

ScoreSystem::ScoreSystem()
{
	currentScore = 0;
}

void ScoreSystem::SaveScore(std::string Username)
{

	//std::fstream newfile;
	//std::fstream file;

	file.open("Score.txt", std::ios::app);
	if (file)
	{
		//std::cout << "File Exists";
		//file.open
		//file.open("Score.txt", std::ios::app);
		file << Username << "-" << currentScore << "\n";
		file.close();

	}
	else
	{
		//file.close();
		std::cout << "File Doesn't Exist";
		file.open("Score.txt", std::ios::out);
		file << Username << "-" << currentScore << "\n";
		file.close();
	}


}

void ScoreSystem::ReadScores()
{
	//Read the Scores sort from high to low and put the top 10 on the screen if there is 10
	//Once sorted is it worth writing them back to the file in a sorted order?
 
	
	SortScores();
	
	/*file.open("Score.txt", std::ios::in);

	file.close();*/

	file.open("Score.txt");
	int lineCount = 0;
	std::string line, m_Name;
	size_t pos = 0;
	std::string delim = "-";

	for (int i = 0; i < 11 && std::getline(file, line); i++)
	{
		//std::cout << line << std::endl;
		while ((pos = line.find(delim)) != std::string::npos)
		{
			m_Name = line.substr(0, pos);
			//std::cout << m_Name << " :token1" << std::endl;
			m_FileData[i].Name = m_Name;
			line.erase(0, pos + delim.length());
			m_FileData[i].Score = std::stoi(line);
		}
		//std::cout << line << "outside while" << std::endl;
		//std::cout << m_FileData[i].Name << "\n" << m_FileData[i].Score << std::endl;

	}
	file.close();
	SortScores();
	std::cout << m_FileData[0].Score << std::endl;
	UpdateScoreFile();

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
#pragma once
#include "Core/Component.h"
#include "Util/SingletonTemplate.h"
#include<string>
#include <fstream>

struct FileData
{
	std::string Name;
	int Score;
};

class ScoreSystem : public SingletonTemplate<ScoreSystem> //public Component 
{
public:
	void setScore(int scoreToSet) { currentScore = scoreToSet; }
	void addScore(int scoreToSet) { currentScore += scoreToSet; }
	float getScore() { return currentScore; }
	ScoreSystem();

	void SaveScore(std::string Username);
	void ReadScores(bool FromMainMenu);
	void RenderTopScores();

	void SortScores();
	void UpdateScoreFile();

private:
	int currentScore;


	std::fstream file;

	FileData m_FileData[13];

};

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

	//Update Score Trackers
	void setEnemiesKilled(int scoreToSet) { enemiesKilled = scoreToSet; }
	void addEnemiesKilled(int scoreToSet) { enemiesKilled += scoreToSet; }
	int getEnemiesKilled() { return enemiesKilled; }

	void setDamageTaken(int scoreToSet) { damageTaken = scoreToSet; }
	void addDamageTaken(int scoreToSet) { damageTaken += scoreToSet; }
	int getDamageTaken() { return damageTaken; }

	void setTilesMoved(int scoreToSet) { tilesMoved = scoreToSet; }
	void addTilesMoved(int scoreToSet) { tilesMoved += scoreToSet; }
	int getTilesMoved() { return tilesMoved; }

	void setGoldEarned(int scoreToSet) { goldEarned = scoreToSet; }
	void addGoldEarned(int scoreToSet) { goldEarned += scoreToSet; }
	int getGoldEarned() { return goldEarned; }

	//Calculate Final Score (Do this on player killed or victory)
	void calcFinalScore();

	void resetScoreSystem();

private:
	int currentScore;
	int enemiesKilled;
	int damageTaken;
	int tilesMoved;
	int goldEarned;

	std::fstream file;

	FileData m_FileData[13];

};

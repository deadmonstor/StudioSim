#pragma once
#include "Core/Component.h"
#include "Util/SingletonTemplate.h"
#include<string>

class ScoreSystem : public SingletonTemplate<ScoreSystem> //public Component 
{
public:
	void setScore(int scoreToSet) { currentScore = scoreToSet; }
	void addScore(int scoreToSet) { currentScore += scoreToSet; }
	float getScore() { return currentScore; }
	ScoreSystem();

	void SaveScore(std::string Username);
	void ReadScores();

private:
	int currentScore;

};

/*#include "Util/SingletonTemplate.h"
#include "Util/Events/EngineEvents.h"
#include <queue>


class TurnManager : public SingletonTemplate<TurnManager>*/
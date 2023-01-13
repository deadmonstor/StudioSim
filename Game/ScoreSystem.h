#pragma once
#include "Core/Component.h"
#include "Util/SingletonTemplate.h"

class ScoreSystem : public SingletonTemplate<ScoreSystem> //public Component 
{
public:
	void setScore(float scoreToSet) { currentScore = scoreToSet; }
	float getScore() { return currentScore; }

	void SaveScore();
	ScoreSystem();

private:
	float currentScore;

};

/*#include "Util/SingletonTemplate.h"
#include "Util/Events/EngineEvents.h"
#include <queue>


class TurnManager : public SingletonTemplate<TurnManager>*/
#pragma once
//#include "EngineSingletonTemplate.h"
#include "Util/SingletonTemplate.h"
#include "Util/Events/EngineEvents.h"
#include <queue>


class TurnManager : public SingletonTemplate<TurnManager>
{
public:
	void addToTurnQueue(class GameObject* object);
	void onUpdate(OnEngineUpdate* event);
	TurnManager();
	void StartTurnSystem();
	void EndTurn();
protected:

private:
	std::queue<class GameObject*> CanMakeATurn;
	void NextTurn();
	
	GameObject* m_CurrentTurnObject;
};

class onStartTurn : public Griddy::Event
{
public:
	onStartTurn(GameObject* object) : objectToStart(object) {};
	GameObject* objectToStart;
};


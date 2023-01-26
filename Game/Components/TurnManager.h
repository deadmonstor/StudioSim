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
	void onGameObjectRemoved(const OnGameObjectRemoved* event);
	TurnManager();
	void StartTurnSystem();
	void EndTurn();
	bool isCurrentTurnObject(const GameObject* object);
protected:

private:
	std::queue<class GameObject*> CanMakeATurn;
	void NextTurn();
	void debugString();

	GameObject* m_CurrentTurnObject;

	friend class ImGuiHandler;
};

class onStartTurn : public Griddy::Event
{
public:
	onStartTurn(GameObject* object) : objectToStart(object) {};
	GameObject* objectToStart;
};


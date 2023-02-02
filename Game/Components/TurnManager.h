#pragma once
#include <queue>
#include "Core/Scene.h"
#include "Util/SingletonTemplate.h"
#include "Util/Events/EngineEvents.h"


class TurnManager : public SingletonTemplate<TurnManager>
{
public:
	TurnManager();
	
	void addToTurnQueue(GameObject* object);
	void onUpdate(OnEngineUpdate* event);
	void onGameObjectRemoved(const OnGameObjectRemoved* event);
	void startTurnSystem();
	void endTurn();
	bool isCurrentTurnObject(const GameObject* object);

	static bool gNoclipMode;
private:
	std::queue<GameObject*> canMakeATurn;
	bool shouldGoNextTurn = false;
	void onDebugEvent(const OnDebugEventChanged* event);
	void onSceneChanged(OnSceneChanged* scene);
	void nextTurn();
	void debugString();

	GameObject* m_CurrentTurnObject;

	friend class ImGuiHandler;
};

class onStartTurn : public Griddy::Event
{
public:
	explicit onStartTurn(GameObject* object) : objectToStart(object) {}
	GameObject* objectToStart;
};


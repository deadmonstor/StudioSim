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

protected:

private:
	std::queue<class GameObject*> CanMakeATurn;

};


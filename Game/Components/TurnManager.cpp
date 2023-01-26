#include "TurnManager.h"
#include "TurnComponent.h"
#include "Core/GameObject.h"
#include "Util/Events/Events.h"

TurnManager::TurnManager()
{
	Griddy::Events::subscribe(this, &TurnManager::onUpdate);
	//Griddy::Event()
		//Griddy::Event
}

void TurnManager::addToTurnQueue(GameObject* object)
{
	CanMakeATurn.push(object);
	//object->addComponent<TurnComponent>();
	
}

void TurnManager::onUpdate(OnEngineUpdate* event)
{
	//LOG_INFO("TEST");
}

void TurnManager::NextTurn()
{
	m_CurrentTurnObject = CanMakeATurn.front();
	CanMakeATurn.pop();
	Griddy::Events::invoke<onStartTurn>(m_CurrentTurnObject);
}

void TurnManager::EndTurn()
{
	CanMakeATurn.push(m_CurrentTurnObject);
	NextTurn();
}

//Called when the last enemy is spawned.
void TurnManager::StartTurnSystem()
{
	NextTurn();
}
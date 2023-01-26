#include "TurnManager.h"
#include "TurnComponent.h"
#include "Core/GameObject.h"
#include "Util/Events/Events.h"

TurnManager::TurnManager()
{
	Griddy::Events::subscribe(this, &TurnManager::onUpdate);
	Griddy::Events::subscribe(this, &TurnManager::onGameObjectRemoved);
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

void TurnManager::onGameObjectRemoved(const OnGameObjectRemoved* event)
{
	if (event->gameObject == m_CurrentTurnObject)
	{
		EndTurn();
	}
}

void TurnManager::NextTurn()
{
	if (CanMakeATurn.empty())
		return;
	
	m_CurrentTurnObject = CanMakeATurn.front();
	CanMakeATurn.pop();

	if (m_CurrentTurnObject != nullptr && !m_CurrentTurnObject->isBeingDeleted())
	{
		Griddy::Events::invoke<onStartTurn>(m_CurrentTurnObject);
	}
	else
	{
		NextTurn();
	}
}

bool TurnManager::isCurrentTurnObject(const GameObject* object)
{
	return m_CurrentTurnObject == object;
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
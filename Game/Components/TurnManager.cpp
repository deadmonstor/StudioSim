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

void TurnManager::debugString()
{
	ImGui::Indent();
	
	ImGui::Text("Current Turn Object: %s", m_CurrentTurnObject->getName().c_str());
	ImGui::Text("CanMakeATurn: %d", CanMakeATurn.size());

	if (ImGui::TreeNode("Objects: "))
	{
		std::queue<GameObject*> tempQueue = CanMakeATurn;
		while (!tempQueue.empty())
		{
			const GameObject* object = tempQueue.front();
			tempQueue.pop();
			ImGui::Text("%s", object->getName().c_str());
		}
		ImGui::TreePop();
	}
	
	ImGui::Unindent();
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
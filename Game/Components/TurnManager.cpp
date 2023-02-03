#include "TurnManager.h"
#include "Core/GameObject.h"
#include "Core/Components/Transform.h"
#include "Core/Grid/PathfindingMachine.h"
#include "Core/Renderer/Renderer.h"
#include "Player/PlayerController.h"
#include "Util/Events/Events.h"

bool TurnManager::gNoclipMode = false;

TurnManager::TurnManager()
{
	Griddy::Events::subscribe(this, &TurnManager::onUpdate);
	Griddy::Events::subscribe(this, &TurnManager::onGameObjectRemoved);
	Griddy::Events::subscribe(this, &TurnManager::onSceneChanged);
	Griddy::Events::subscribe(this, &TurnManager::onDebugEvent);
}

void TurnManager::addToTurnQueue(GameObject* object)
{
	canMakeATurn.push(object);
}

void TurnManager::onUpdate(OnEngineUpdate* event)
{
	if (shouldGoNextTurn)
	{
		shouldGoNextTurn = false;
		nextTurn();
	}
}

void TurnManager::onGameObjectRemoved(const OnGameObjectRemoved* event)
{
	if (event->gameObject == m_CurrentTurnObject && !SceneManager::Instance()->isLoadingScene())
	{
		endTurn();
	}
}

void TurnManager::onDebugEvent(const OnDebugEventChanged* event)
{
	if (event->key == DebugNoclip)
	{
		gNoclipMode = !gNoclipMode;
	}
}

void TurnManager::onSceneChanged(OnSceneChanged* scene)
{
	canMakeATurn = std::queue<GameObject*>();
}

void TurnManager::nextTurn()
{
	if (canMakeATurn.empty())
		return;
	
	m_CurrentTurnObject = canMakeATurn.front();
	canMakeATurn.pop();

	if (m_CurrentTurnObject != nullptr &&
		!m_CurrentTurnObject->isBeingDeleted())
	{
		if (!Renderer::Instance()->getCamera()->isInFrustum(
			m_CurrentTurnObject->getTransform()->getPosition(),
			m_CurrentTurnObject->getTransform()->getScale()) && m_CurrentTurnObject != PlayerController::Instance()->playerPTR)
		{
			canMakeATurn.push(m_CurrentTurnObject);
			m_CurrentTurnObject = nullptr;
			nextTurn();
			return; //We don't want to invoke the event if the object is not in the camera's frustum.
		}

		// check line of sight from player to the enemy
		if (m_CurrentTurnObject != PlayerController::Instance()->playerPTR)
		{
			const auto playerPos = m_CurrentTurnObject->getTransform()->getPosition();
			const auto enemyPos = PlayerController::Instance()->playerPTR->getTransform()->getPosition();
			
			if (!PathfindingMachine::Instance()->LineOfSight(GridSystem::Instance()->getTilePosition(playerPos), GridSystem::Instance()->getTilePosition(enemyPos)))
			{
				canMakeATurn.push(m_CurrentTurnObject);
				m_CurrentTurnObject = nullptr;
				nextTurn();
				return; //We don't want to invoke the event if the object is not in the camera's frustum.
			}
		}

		if (auto* cam = m_CurrentTurnObject->getComponent<Camera>(); cam != nullptr)
		{
			//6Renderer::Instance()->setCamera(cam);
		}
		
		Griddy::Events::invoke<onStartTurn>(m_CurrentTurnObject);
	}
	else
	{
		nextTurn();
	}
}

void TurnManager::debugString()
{
	ImGui::Indent();
	
	ImGui::Text("Current Turn Object: %s", m_CurrentTurnObject != nullptr ? m_CurrentTurnObject->getName().c_str() : "No Object");
	ImGui::Text("CanMakeATurn: %d", canMakeATurn.size());

	if (ImGui::TreeNode("Objects: "))
	{
		std::queue<GameObject*> tempQueue = canMakeATurn;
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

void TurnManager::endTurn()
{
	canMakeATurn.push(m_CurrentTurnObject);
	shouldGoNextTurn = true;
}

//Called when the last enemy is spawned.
void TurnManager::startTurnSystem()
{
	nextTurn();
}
#include "TurnManager.h"
#include "TurnComponent.h"
#include "Core/GameObject.h"
#include "Util/Events/Events.h"

TurnManager::TurnManager()
{
	Griddy::Events::subscribe(this, &TurnManager::onUpdate);
}

void TurnManager::addToTurnQueue(GameObject* object)
{
	CanMakeATurn.push(object);
	object->addComponent<TurnComponent>();
}

void TurnManager::onUpdate(OnEngineUpdate* event)
{
	LOG_INFO("TEST");
}

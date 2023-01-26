#include "TurnComponent.h"
#include "TurnManager.h"

//Called when the turn manager 
void TurnComponent::StartTurn()
{
	if (m_Owner == nullptr)
	{
		m_Owner == getOwner();
	}
	
}

//Called when a player or enemy finishes the turn and gets the turn manager to call
void TurnComponent::EndTurn()
{
	//TurnManager::Instance()->EndTurn();

}

void TurnComponent::SetOwner()
{
	m_Owner = getOwner();
}

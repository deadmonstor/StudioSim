#pragma once
#include "Core/Component.h"
#include "Util/Events/EngineEvents.h"


class TurnComponent : public Component
{
public:
	void StartTurn();
	void EndTurn();
	void SetOwner();


protected:


private:
	GameObject* m_Owner;

};
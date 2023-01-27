#pragma once
#include "Util/SingletonTemplate.h"
#include "Util/Events/EngineEvents.h"
#include "../Game/Components/ButtonComponent.h"

class UIManager : public SingletonTemplate<UIManager>
{
	std::map<std::string, ButtonComponent*> buttons;

public:
	void render();
	void internalRender();
	void addButtonToUI(std::string nameOfUIElement, ButtonComponent* button);
};


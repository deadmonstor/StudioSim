#include "UIManager.h"

void UIManager::render()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	for (auto const& [name, button] : buttons)
	{
		button->render();
	}
	glDisable(GL_BLEND);
}

void UIManager::internalRender()
{

}

void UIManager::addButtonToUI(std::string nameOfUIElement, ButtonComponent* button)
{
	buttons[nameOfUIElement] = button;
}

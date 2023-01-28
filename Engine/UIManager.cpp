#include "UIManager.h"

#include <ranges>
#include <glad/glad.h>
#include "Core/Components/UI/Panel.h"

void UIManager::render()
{
	for (const auto& panel : UIElements | std::views::values)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			panel->render();
		glDisable(GL_BLEND);
	}
}

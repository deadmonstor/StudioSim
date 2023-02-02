#include "UIManager.h"

#include <ranges>
#include <glad/glad.h>

#include "../Game/Components/Player/PlayerController.h"
#include "Core/Components/UI/Panel.h"

void UIManager::render()
{
	if (SceneManager::Instance()->isLoadingScene() ||
		SceneManager::Instance()->isShuttingDown())
		return;
	
	for (const auto& panel : UIElements | std::views::values)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			panel->render();
		glDisable(GL_BLEND);
	}
}

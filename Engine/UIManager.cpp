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
	
	for (const auto& panel : renderPanels)
	{
		if (!panel->shouldRender)
			continue;
		
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			panel->render();
		glDisable(GL_BLEND);
	}
}

void UIManager::clear()
{
	for (const auto& panel : UIElements | std::views::values)
	{
		panel->destroy();
		delete panel;
	}

	renderPanels.clear();
	UIElements.clear();
}

void UIManager::sortOrder()
{
	renderPanels.clear();
	for(auto it = UIElements.begin(); it != UIElements.end(); ++it )
	{
		renderPanels.push_back( it->second );
	}

	std::ranges::sort(renderPanels, [](const Panel* a, const Panel* b)
	{
		return a->getSortingOrder() < b->getSortingOrder();
	});
}

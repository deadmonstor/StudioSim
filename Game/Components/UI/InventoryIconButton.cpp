#include "InventoryIconButton.h"
#include "Engine.h"
#include "../../System/Inventory.h"
#include "../Player/PlayerController.h"
#include "Core/AudioEngine.h"
#include "Core/Components/TextRenderer.h"
#include "Core/Components/Transform.h"

InventoryIconButton::InventoryIconButton(const Texture& _texture, Item* _item) : ButtonComponent(_texture)
{
	item = _item;
}

void InventoryIconButton::onClick()
{
	AudioEngine::Instance()->playSound("Sounds\\Click.wav", false, 0.2f, 0, 0, AudioType::SoundEffect);
	setColor({ 1, 0, 0 });

	Inventory* inventory = PlayerController::Instance()->myInventory;
	
	if (item != nullptr && inventory != nullptr)
	{
		if (item->isEquipped)
			inventory->unequip_item(item->name());
		else if (item->isEquipable())
			inventory->equip_item(item->name());
		else if (item->isUsable())
			inventory->use_item(item->name());
	}
}

void InventoryIconButton::render()
{
	ButtonComponent::render();
	
	if (isMouseInButton())
	{
		setColor({ 0.5, 0.5, 0.5 });

		if (item != nullptr)
		{
			const std::string text = item->name();
			const glm::vec2 position = getTransform()->getPosition();
			glm::vec2 sizeOfText = TextRenderer::Instance()->renderTextSize(text, 0.5);
			TextRenderer::Instance()->renderText(text,
				position.x - sizeOfText.x,
				position.y + sizeOfText.y / 2,
				0.51,
				{0, 0, 0},
				glm::vec2{0.5f, 0.5f}
			);
			
			TextRenderer::Instance()->renderText(text,
				position.x - sizeOfText.x,
				position.y + sizeOfText.y / 2,
				0.5,
				{1, 1, 1},
				glm::vec2{0.5f, 0.5f}
			);
		}
	}
}




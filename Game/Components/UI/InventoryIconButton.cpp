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

void InventoryIconButton::update()
{
	if (isMouseInButton())
	{
		setColor({ 0.5, 0.5, 0.5 });
		if (item != nullptr)
		{
			std::string text = item->name();
			const glm::vec2 sizeOfText = TextRenderer::Instance()->renderTextSize("asdasd", 1);
			TextRenderer::Instance()->renderText("asdasd",
				500,
				500,
				1,
				glm::vec3(1, 1, 1),
				glm::vec2{ 0.5f, 0.5f }
			);
		}
	}
}




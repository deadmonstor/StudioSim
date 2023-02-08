#include "InventoryIconButton.h"
#include "Engine.h"
#include "../../System/Inventory.h"
#include "../Player/PlayerController.h"
#include "Core/AudioEngine.h"

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



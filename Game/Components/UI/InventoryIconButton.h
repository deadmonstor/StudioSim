#pragma once
#include "ButtonComponent.h"
class Item;

class InventoryIconButton final : public ButtonComponent
{
	Item* item;
	
public:
	InventoryIconButton(const Texture& _texture, Item* _item);
	void onClick() override;
};

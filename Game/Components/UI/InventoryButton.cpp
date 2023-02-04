#include "InventoryButton.h"

InventoryButton::InventoryButton(const Texture& _texture) : ButtonComponent(_texture)
{
}

void InventoryButton::onClick()
{
	setColor({ 1, 0, 0 });
	std::cout << "Inventory Clicked\n";
}

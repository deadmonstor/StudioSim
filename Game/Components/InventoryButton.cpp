#include "UI/InventoryButton.h"
#include "Engine.h"

InventoryButton::InventoryButton(const Texture& _texture) : ButtonComponent(_texture)
{

}

void InventoryButton::onClick()
{
	setColor({ 1, 0, 0 });
	std::cout << "Inventory Pressed \n";
}
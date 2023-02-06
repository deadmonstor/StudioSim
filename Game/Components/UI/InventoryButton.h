#pragma once
#include "ButtonComponent.h"
class InventoryButton final : public ButtonComponent
{
public:
	InventoryButton(const Texture& _texture);
	void onClick() override;
};




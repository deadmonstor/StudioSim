#pragma once
#include "ButtonComponent.h"
class PauseButton final : public ButtonComponent
{
public:
	PauseButton(const Texture& _texture);
	void onClick() override;
};


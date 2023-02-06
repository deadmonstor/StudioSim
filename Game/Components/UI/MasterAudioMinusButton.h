#pragma once
#include "ButtonComponent.h"
class MasterAudioMinusButton final : public ButtonComponent
{
public:
	MasterAudioMinusButton(const Texture& _texture);
	void onClick() override;
};
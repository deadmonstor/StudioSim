#pragma once
#include "ButtonComponent.h"
class MasterAudioPlusButton final : public ButtonComponent
{
public:
	MasterAudioPlusButton(const Texture& _texture);
	void onClick() override;
};


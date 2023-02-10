#pragma once
#include "ButtonComponent.h"
class MasterAudioMuteButton final : public ButtonComponent
{
public:
	MasterAudioMuteButton(const Texture& _texture);
	void onClick() override;
};
#include "MasterAudioMinusButton.h"

MasterAudioMinusButton::MasterAudioMinusButton(const Texture& _texture) : ButtonComponent(_texture)
{
}

void MasterAudioMinusButton::onClick()
{
	setColor({ 1, 0, 0 });
	std::cout << "Audio Minus Clicked\n";
}

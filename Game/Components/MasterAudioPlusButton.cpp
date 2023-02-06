#include "UI/MasterAudioPlusButton.h"
#include "Engine.h"

MasterAudioPlusButton::MasterAudioPlusButton(const Texture& _texture) : ButtonComponent(_texture)
{

}

void MasterAudioPlusButton::onClick()
{
	setColor({ 1, 0, 0 });
	std::cout << "Plus Audio \n";
}



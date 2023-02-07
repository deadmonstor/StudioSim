#include "MasterAudioPlusButton.h"
#include "Engine.h"
#include "Core/AudioEngine.h"

MasterAudioPlusButton::MasterAudioPlusButton(const Texture& _texture) : ButtonComponent(_texture)
{

}

void MasterAudioPlusButton::onClick()
{
	AudioEngine::Instance()->playSound("Sounds\\Click.wav", false, 0.2f, 0, 0, AudioType::SoundEffect);
	setColor({ 1, 0, 0 });
	std::cout << "Plus Audio \n";
}



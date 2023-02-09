#include "MasterAudioMinusButton.h"
#include "Engine.h"
#include "Core/AudioEngine.h"

MasterAudioMinusButton::MasterAudioMinusButton(const Texture& _texture) : ButtonComponent(_texture)
{

}

void MasterAudioMinusButton::onClick()
{
	AudioEngine::Instance()->playSound("Sounds\\Click.wav", false, 0.2f, 0, 0, AudioType::SoundEffect);
	setColor({ 1, 0, 0 });
	std::cout << "Minus Audio " << AudioEngine::Instance()->masterVolume - 0.1f <<"\n";
	AudioEngine::Instance()->setVolumeChannelGroup("Master Channel", (AudioEngine::Instance()->masterVolume - 0.1f));
}



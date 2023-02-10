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
	if (AudioEngine::Instance()->getChannelGroupMuted("Master Channel"))
	{
		AudioEngine::Instance()->setMuteChannelGroup("Master Channel", false);
	}
	AudioEngine::Instance()->setVolumeChannelGroup("Master Channel", (AudioEngine::Instance()->masterVolume + 0.1f));
}



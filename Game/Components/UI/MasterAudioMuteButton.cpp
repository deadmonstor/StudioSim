#include "MasterAudioMuteButton.h"
#include "Engine.h"
#include "Core/AudioEngine.h"

MasterAudioMuteButton::MasterAudioMuteButton(const Texture& _texture) : ButtonComponent(_texture)
{

}

void MasterAudioMuteButton::onClick()
{
	AudioEngine::Instance()->playSound("Sounds\\Click.wav", false, 0.2f, 0, 0, AudioType::SoundEffect);
	setColor({ 1, 0, 0 });
	AudioEngine::Instance()->setMuteChannelGroup("Master Channel", !AudioEngine::Instance()->getChannelGroupMuted("Master Channel"));
}

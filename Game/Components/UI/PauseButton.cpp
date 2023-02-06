#include "PauseButton.h"
#include "Engine.h"
#include "Core/AudioEngine.h"

PauseButton::PauseButton(const Texture& _texture) : ButtonComponent(_texture)
{

}

void PauseButton::onClick()
{
	AudioEngine::Instance()->playSound("Sounds\\Click.wav", false, 0.2f, 0, 0, AudioType::SoundEffect);
	setColor({ 1, 0, 0 });
	Griddy::Engine::setPaused(true);
}



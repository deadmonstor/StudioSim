#include "BossMusic.h"
#include <Core/Renderer/ResourceManager.h>
#include <Core/AudioEngine.h>


void BossMusic::Initialise()
{
	Griddy::Events::subscribe(this, &BossMusic::PlayMusic);
	Griddy::Events::subscribe(this, &BossMusic::StopMusic);
}

void BossMusic::PlayMusic(EnterBossRoomEvent* event)
{
	if (!ResourceManager::HasSound("Sounds\\CrabRave.mp3"))
		AudioEngine::Instance()->loadSound("Sounds\\CrabRave.mp3", FMOD_3D);
	AudioEngine::Instance()->playSound("Sounds\\CrabRave.mp3", false, 0.1f, 0, 0, AudioType::BackgroundMusic);
}

void BossMusic::StopMusic(BossDeathEvent* event)
{
	AudioEngine::Instance()->playSound("Sounds\\MainTheme.wav", false, 0.1f, 0, 0, AudioType::BackgroundMusic);
}

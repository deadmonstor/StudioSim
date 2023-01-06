#pragma once
#include "Util/SingletonTemplate.h"
#include "Util/Audio/inc/fmod.h"
#include "Util/Audio/inc/fmod_errors.h"
#include "Util/Audio/inc/fmod.hpp"
#include "Util//Audio/inc/fmod_common.h"
#include "Util/Logger.h"
class AudioEngine : public SingletonTemplate<AudioEngine>
{
public:
	bool init();
	void update();
	bool checkResult(FMOD_RESULT fmodResult);
	bool loadSound(const char* path, FMOD_MODE fMode);
	bool playSound(const char *path, bool isPaused, float volume);

	FMOD::System *fmodSystem = NULL;

	//Store all of the sounds in the game
	std::map<std::string, FMOD::Sound*> loadedSounds;

	//Store all of the current channels
	std::map<int, FMOD::Channel *> currentChannels;
};


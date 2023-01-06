#include "AudioEngine.h"

bool AudioEngine::init() 
{ 

	//To Do Abstract Into Classes
	FMOD_RESULT fmodResult;

	//Create the System
	fmodResult = FMOD::System_Create(&fmodSystem);

	//Check if it was created
	if (fmodResult != FMOD_OK) 
	{
		LOG_ERROR("FMod failed to create the system");
		return false;
	}

	//Create the channels, flags set to normal
	fmodResult = fmodSystem->init(512, FMOD_INIT_NORMAL, 0);
	if (fmodResult != FMOD_OK) 
	{
		LOG_ERROR("FMod failed to initialise the system");
		return false;
	}
}

void AudioEngine::update() 
{ 
	//System must be updated once per cycle
	fmodSystem->update(); 
}

bool AudioEngine::loadSound(const char *path, FMOD_MODE fMode) 
{ 
	//Check if sound exists
	if (loadedSounds.contains(path)) 
	{
		//Already Loaded
		LOG_ERROR("Trying to load already loaded sound");
		return false;
	}
	else
	{
		FMOD::Sound *fmodSound = nullptr;
		fmodSystem->createSound(path, FMOD_2D, nullptr, &fmodSound);
		loadedSounds[path] = fmodSound;
		return true;
	}
}

bool AudioEngine::playSound(const char *path, bool isPaused, float volume)
{
	//const char *path = "Sounds\\griddy.mp3";

	FMOD::Sound* sound = loadedSounds[path];
	// Test Create Channel
	FMOD::Channel *fmodChannel = nullptr;
	fmodSystem->playSound(sound, nullptr, isPaused, &fmodChannel);
	fmodChannel->setVolume(volume);
	return true;
}





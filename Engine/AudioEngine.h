#pragma once
#include "Util/SingletonTemplate.h"
#include "Core/Renderer/ResourceManager.h"
#include "Util/Logger.h"
#include "Util/Events/EngineEvents.h"

class AudioEngine : public SingletonTemplate<AudioEngine>
{
public:
	bool init();
	void update();
	bool checkResult(FMOD_RESULT fmodResult);
	bool loadSound(const char* path, FMOD_MODE fMode);
	bool playSound(const char *path, bool isPaused, float volume, float positionX, float positionY);
	void onDebugEvent(const OnDebugEventChanged* event);
	void updateListenerPositon(float positionX, float positionY);
	FMOD::System *fmodSystem = NULL;

	//Store all of the sounds in the game
	//std::map<std::string, FMOD::Sound*> loadedSounds;

	FMOD_VECTOR listenerPosition;

	//Store all of the current channels
	std::map<int, FMOD::Channel *> currentChannels;
};


#pragma once
#include "Util/SingletonTemplate.h"
#include "Core/Renderer/ResourceManager.h"
#include "Util/Logger.h"
#include "Util/Events/EngineEvents.h"

enum class AudioType
{
	SoundEffect = 1,
	BackgroundMusic = 2
};
DEFINE_ENUM_FLAG_OPERATORS(AudioType);

class AudioEngine : public SingletonTemplate<AudioEngine>
{
public:
	bool init();
	void update();
	bool checkResult(FMOD_RESULT fmodResult, std::string area);
	bool loadSound(const char* path, FMOD_MODE fMode);
	bool playSound(const char *path, bool isPaused, float volume, float positionX, float positionY, AudioType audioType);
	void onDebugEvent(const OnDebugEventChanged* event);
	void updateListenerPositon(float positionX, float positionY);
	FMOD::System *fmodSystem = NULL;

	//Store all of the sounds in the game
	//std::map<std::string, FMOD::Sound*> loadedSounds;

	FMOD_VECTOR listenerPosition = {0, 0, 0};

	//Store all of the current channels
	std::unordered_map<int, FMOD::Channel *> currentChannels;

	//FMod Channel Groups
	std::unordered_map<std::string, FMOD::ChannelGroup*> channelGroups;

	//Store reverb zones
	std::unordered_map<const int, FMOD::Reverb3D*> reverbZones;
	bool createReverbZone(const int zone);
	bool setReverbPos(const int zone, const float posX, const float posY, const float minX, const float minY);
	bool deleteReverbZone(const int zone);

	//Channel Stuff
	FMOD::ChannelGroup* masterChannel;
	FMOD::ChannelGroup* audioEffectsChannel;
	FMOD::ChannelGroup* backgroundMusicChannel;
};


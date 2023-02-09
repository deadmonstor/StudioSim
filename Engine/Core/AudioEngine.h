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
	bool playSound(const char *path, bool isPaused, float volume, float positionX, float positionY, AudioType audioType); //Pass in Position of Sound
	void onDebugEvent(const OnDebugEventChanged* event);
	void updateListenerPositon(float positionX, float positionY); //Update with Player Position
	FMOD::System *fmodSystem = NULL;

	//Store all of the sounds in the game
	//std::map<std::string, FMOD::Sound*> loadedSounds;

	FMOD_VECTOR listenerPosition = {0, 0, 0};

	//Store all of the current channels
	std::map<int, FMOD::Channel *> currentChannels;

	//FMod Channel Groups
	std::map<std::string, FMOD::ChannelGroup*> channelGroups;
	bool stopChannelGroup(std::string channelGroupName);
	bool setPauseChannelGroup(std::string channelGroupName, bool pause);
	bool setModeChannelGroup(std::string channelGroupName, FMOD_MODE modes);
	bool setPitchChannelGroup(std::string channelGroupName, float pitch);
	bool setVolumeChannelGroup(std::string channelGroupName, float volume);
	bool setMuteChannelGroup(std::string channelGroupName, bool mute);
	bool set3DAttributeChannelGroup(std::string channelGroupName, FMOD_VECTOR pos, FMOD_VECTOR vel);
	bool setMinMaxChannelGroup(std::string channelGroupName, float min, float max);
	int getNumberOfChannelsInGroup(std::string channelGroupName);
	float getChannelVolume(std::string channelGroupName);

	//Channel Stuff
	FMOD::ChannelGroup* masterChannel;
	FMOD::ChannelGroup* audioEffectsChannel;
	FMOD::ChannelGroup* backgroundMusicChannel;

	//Background Channel
	FMOD::Channel* backgroundChannel;
	FMOD::Channel* backgroundChannel2;

	//Reverb zones
	std::map<const int, FMOD::Reverb3D*> reverbZones;
	bool createReverbZone(const int zone);
	bool setReverbPos(const int zone, const float posX, const float posY, const float minX, const float minY);
	bool deleteReverbZone(const int zone);

	bool firstRun = false;
	float masterVolume = 1.0f;
	int backgroundChannelIndex = 0, backgroundChannel2Index = 0;
};


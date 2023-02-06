#include "AudioEngine.h"

#include "Util/Events/EngineEvents.h"
#include "Util/Events/Events.h"

class OnDebugEventChanged;

bool AudioEngine::init() 
{ 
	//To Do Abstract Into Classes
	FMOD_RESULT fmodResult;

	//Create the System
	fmodResult = FMOD::System_Create(&fmodSystem);

	//Check if it was created
	if (!checkResult(fmodResult, "Create System")) {
		return false;
	}

	//Create the channels, flags set to normal
	fmodResult = fmodSystem->init(512, FMOD_INIT_NORMAL, 0);
	if (!checkResult(fmodResult, "Intialising")) 
	{
		return false;
	}

	//One listener (player)
	fmodResult = fmodSystem->set3DNumListeners(1);
	if (!checkResult(fmodResult, "Set Listeners"))
	{
		return false;
	}
	
	//Default factors
	fmodResult = fmodSystem->set3DSettings(1, 1, 1);
	if (!checkResult(fmodResult, "Set 3D Settings System"))
	{
		return false;
	}

	//Set Master Group
	fmodResult = fmodSystem->getMasterChannelGroup(&masterChannel);
	if (!checkResult(fmodResult, "Failed to get master channel"))
	{
		return false;
	}
	channelGroups["Master Channel"] = masterChannel;

	//Create groups
	fmodResult = fmodSystem->createChannelGroup("audioSFX",  &audioEffectsChannel);
	if (!checkResult(fmodResult, "Failed to create audioSFX channel"))
	{
		return false;
	}
	channelGroups["Audio SFX"] = audioEffectsChannel;
	
	fmodResult = audioEffectsChannel->setMode(FMOD_3D);
	if (!checkResult(fmodResult, "Audio Set Mode 3D"))
	{
		return false;
	}

	fmodResult = audioEffectsChannel->setMode(FMOD_3D_LINEARROLLOFF);
	if (!checkResult(fmodResult, "Audio Set Roll Off"))
	{
		return false;
	}

	fmodResult = fmodSystem->createChannelGroup("backgroundMusic", &backgroundMusicChannel);
	if (!checkResult(fmodResult, "Failed to create backgroundMusic channel"))
	{
		return false;
	}
	channelGroups["Background Music"] = backgroundMusicChannel;
	fmodResult = backgroundMusicChannel->setMode(FMOD_3D);
	if (!checkResult(fmodResult, "Background Set Mode 3D"))
	{
		return false;
	}

	fmodResult = backgroundMusicChannel->setMode(FMOD_3D_LINEARROLLOFF);
	if (!checkResult(fmodResult, "Background Set Roll Off"))
	{
		return false;
	}

	//Add audio channel groups
	masterChannel->addGroup(audioEffectsChannel);
	masterChannel->addGroup(backgroundMusicChannel);

	Griddy::Events::subscribe(this, &AudioEngine::onDebugEvent);

	return true;
}

void AudioEngine::update() 
{
	FMOD_RESULT fmodResult;

	//Position of listener
	// Test Function
	//updateListenerPositon(listenerPosition.x - 1, 0); 
	const FMOD_VECTOR listenerPos = {listenerPosition.x, listenerPosition.y, 0};

	//forward/up vectors left at default for now (probably not needed)
	//const FMOD_VECTOR forward = FMOD_VECTOR(0, 0, 0);
	//const FMOD_VECTOR up = FMOD_VECTOR(0, 0, 0);

	//Set listener Attributes (Listener ID, Position, Velocity, Forward Vector, Up Vector)
	fmodResult = fmodSystem->set3DListenerAttributes(0, &listenerPos, 0, 0, 0);
	checkResult(fmodResult, "Set 3D listener attributes");

	//System must be updated once per cycle
	fmodSystem->update(); 
}

bool AudioEngine::checkResult(FMOD_RESULT fmodResult, std::string area) 
{
	if (fmodResult != FMOD_OK) 
	{
		LOG_ERROR("FMod failed in " + area);
		return false; 
	}
	return true;
}

bool AudioEngine::loadSound(const char *path, const FMOD_MODE fMode) 
{ 
	//Check if sound exists
	if (ResourceManager::HasSound(path)) 
	{
		LOG_ERROR("Trying to load already loaded sound");
		return false;
	}
	
	ResourceManager::LoadSound(path, fMode, fmodSystem);
	return true;
}

bool AudioEngine::playSound(const char *path, bool isPaused, float volume, float positionX, float positionY, AudioType audioType)
{
	//Debug
	FMOD_RESULT fmodResult;

	//Channel Creation
	FMOD::Channel *fmodChannel = nullptr;

	if (audioType == AudioType::SoundEffect)
	{
		fmodSystem->playSound(ResourceManager::GetSound(path), nullptr, isPaused, &fmodChannel);
		fmodChannel->setMode(FMOD_3D);

		//Audio source position
		FMOD_VECTOR sourcePosition = { positionX, positionY, 0 };

		//Enable Channel Modes
		fmodChannel->setMode(FMOD_3D);
		fmodChannel->setMode(FMOD_3D_LINEARROLLOFF);

		//Set Volume
		fmodResult = fmodChannel->setVolume(volume);
		if (!checkResult(fmodResult, "Set Channel Volume"))
		{
			return false;
		}

		//Set audio position
		fmodResult = fmodChannel->set3DAttributes(&sourcePosition, nullptr);
		if (!checkResult(fmodResult, "Set 3D Channel Attributes"))
		{
			return false;
		}

		//Set min/max falloff
		fmodResult = fmodChannel->set3DMinMaxDistance(10, 1000);
		if (!checkResult(fmodResult, "Set 3D Min/Max Distance"))
		{
			return false;
		}

		fmodChannel->setChannelGroup(channelGroups["Audio SFX"]);
	}
	else
	{
		//std::cout << backgroundChannelIndex << std::endl;
		//														   0
		channelGroups["Background Music"]->getChannel(backgroundChannelIndex, &backgroundChannel);

		//bool backgroundChannelPlaying;
		//backgroundChannel->isPlaying(&backgroundChannelPlaying);


		if (!firstRun)
		{
			firstRun = true;
		}
		else
		{
			backgroundChannel->stop();
		}

		backgroundChannel->getIndex(&backgroundChannelIndex);

		ResourceManager::GetSound(path)->setLoopCount(-1);
		fmodSystem->playSound(ResourceManager::GetSound(path), channelGroups["Background Music"], isPaused, &backgroundChannel);

		//Audio source position
		FMOD_VECTOR sourcePosition = { positionX, positionY, 0 };

		//Enable Channel Modes
		fmodResult = backgroundChannel->setMode(FMOD_3D);
		if (!checkResult(fmodResult, "Set Channel Volume"))
		{
			return false;
		}

		fmodResult = backgroundChannel->setMode(FMOD_LOOP_NORMAL);
		if (!checkResult(fmodResult, "Set Looping"))
		{
			return false;
		}

		fmodResult = backgroundChannel->setMode(FMOD_3D_LINEARROLLOFF);
		if (!checkResult(fmodResult, "Set Channel Volume"))
		{
			return false;
		}

		//Set Volume
		fmodResult = backgroundChannel->setVolume(volume);
		if (!checkResult(fmodResult, "Set Channel Volume"))
		{
			return false;
		}

		//Set audio position
		fmodResult = backgroundChannel->set3DAttributes(&sourcePosition, nullptr);
		if (!checkResult(fmodResult, "Set 3D Channel Attributes"))
		{
			return false;
		}

		//Set min/max falloff
		fmodResult = backgroundChannel->set3DMinMaxDistance(10, 1000);
		if (!checkResult(fmodResult, "Set 3D Min/Max Distance"))
		{
			return false;
		}



		//Loop(0 - Oneshot, 1 - Loop Once and Stop, -1 - Loop Forever
		fmodResult = backgroundChannel->setLoopCount(-1);
		if (!checkResult(fmodResult, "Set Loop"))
		{
			std::cout << "Loop Set\n";
			return false;
		}
	}
	return true;
}

void AudioEngine::onDebugEvent(const OnDebugEventChanged* event)
{
	if (event->key == DebugPlaySound)
	{
		Instance()->loadSound("Sounds\\griddy.mp3", FMOD_3D);
		Instance()->playSound("Sounds\\griddy.mp3", false, 0.1f, 0, 0, AudioType::BackgroundMusic);

		//Instance()->loadSound("Sounds\\doneit.mp3", FMOD_3D);
		//Instance()->playSound("Sounds\\doneit.mp3", false, 0.1f, 10, 10);
	}
}

void AudioEngine::updateListenerPositon(float positionX, float positionY) 
{
	listenerPosition = {positionX, positionY, 0};
}

bool AudioEngine::createReverbZone(const int zone)
{
	//Debug
	FMOD_RESULT fmodResult;

	FMOD::Reverb3D* newReverbZone;
	fmodResult = fmodSystem->createReverb3D(&newReverbZone);
	if (!checkResult(fmodResult, "Create Reverb Zone"))
	{
		return false;
	}

	FMOD_REVERB_PROPERTIES prop2 = FMOD_PRESET_CONCERTHALL;
	newReverbZone->setProperties(&prop2);
	reverbZones[zone] = newReverbZone;
	reverbZones[zone]->setActive(true);
	return true;
}

bool AudioEngine::setReverbPos(const int zone, const float posX, const float posY, const float minX, const float minY)
{
	FMOD_RESULT fmodResult;
	fmodResult = reverbZones[zone]->set3DAttributes(new FMOD_VECTOR{ posX, posY, 0} , minX, minY);
	if (!checkResult(fmodResult, "Set 3D Reverb Zone"))
	{
		return false;
	}
	return true;
}

bool AudioEngine::deleteReverbZone(const int zone)
{
	reverbZones[zone]->setActive(false);
	reverbZones[zone]->release();
	reverbZones.erase(zone);
	return true;
}


//Channel Group Functions
bool AudioEngine::stopChannelGroup(std::string channelGroupName)
{
	FMOD_RESULT fmodResult;
	fmodResult = channelGroups[channelGroupName]->stop();
	if (!checkResult(fmodResult, "stopChannelGroup"))
	{
		return false;
	}
	return true;
}

bool AudioEngine::setPauseChannelGroup(std::string channelGroupName, bool pause)
{
	FMOD_RESULT fmodResult;
	fmodResult = channelGroups[channelGroupName]->setPaused(pause);
	if (!checkResult(fmodResult, "setPauseChannelGroup"))
	{
		return false;
	}
	return true;
}

bool AudioEngine::setModeChannelGroup(std::string channelGroupName, FMOD_MODE modes)
{
	FMOD_RESULT fmodResult;
	fmodResult = channelGroups[channelGroupName]->setMode(modes);
	if (!checkResult(fmodResult, "setModeChannelGroup"))
	{
		return false;
	}
	return true;
}

bool AudioEngine::setPitchChannelGroup(std::string channelGroupName, float pitch)
{
	FMOD_RESULT fmodResult;
	fmodResult = channelGroups[channelGroupName]->setPitch(pitch);
	if (!checkResult(fmodResult, "setPitchChannelGroup"))
	{
		return false;
	}
	return true;
}

bool AudioEngine::setVolumeChannelGroup(std::string channelGroupName, float volume)
{
	FMOD_RESULT fmodResult;
	fmodResult = channelGroups[channelGroupName]->setVolume(volume);
	if (!checkResult(fmodResult, "setVolumeChannelGroup"))
	{
		return false;
	}
	return true;
}

bool AudioEngine::setMuteChannelGroup(std::string channelGroupName, bool mute)
{
	FMOD_RESULT fmodResult;
	fmodResult = channelGroups[channelGroupName]->setMute(mute);
	if (!checkResult(fmodResult, "setMuteChannelGroup"))
	{
		return false;
	}
	return true;
}

bool AudioEngine::set3DAttributeChannelGroup(std::string channelGroupName, FMOD_VECTOR pos, FMOD_VECTOR vel)
{
	FMOD_RESULT fmodResult;
	fmodResult = channelGroups[channelGroupName]->set3DAttributes(&pos, &vel);
	if (!checkResult(fmodResult, "set3DAttributeChannelGroup"))
	{
		return false;
	}
	return true;
}

bool AudioEngine::setMinMaxChannelGroup(std::string channelGroupName, float min, float max)
{
	FMOD_RESULT fmodResult;
	fmodResult = channelGroups[channelGroupName]->set3DMinMaxDistance(min, max);
	if (!checkResult(fmodResult, "setMinMaxChannelGroup"))
	{
		return false;
	}
	return true;
}

int AudioEngine::getNumberOfChannelsInGroup(std::string channelGroupName)
{
	FMOD_RESULT fmodResult;
	int channels;
	fmodResult = channelGroups[channelGroupName]->getNumChannels(&channels);
	if (!checkResult(fmodResult, "getNumberOfChannelsInGroup"))
	{
		return 0;
	}
	return channels;
}

float AudioEngine::getChannelVolume(std::string channelGroupName)
{
	FMOD_RESULT fmodResult;
	float volume;
	fmodResult = channelGroups[channelGroupName]->getVolume(&volume);
	if (!checkResult(fmodResult, "getChannelVolume"))
	{
		return 0;
	}
	return volume;
}

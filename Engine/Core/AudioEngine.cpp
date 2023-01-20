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

	//Create groups
	fmodResult = fmodSystem->createChannelGroup("audioSFX",  &audioEffectsChannel);
	if (!checkResult(fmodResult, "Failed to create audioSFX channel"))
	{
		return false;
	}

	fmodResult = fmodSystem->createChannelGroup("backgroundMusic", &backgroundMusicChannel);
	if (!checkResult(fmodResult, "Failed to create backgroundMusic channel"))
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
	if (ResourceManager::GetSound(path) != nullptr) 
	{
		LOG_ERROR("Trying to load already loaded sound");
		return false;
	}
	
	ResourceManager::LoadSound(path, fMode, fmodSystem);
	return true;
}

bool AudioEngine::playSound(const char *path, bool isPaused, float volume, float positionX, float positionY)
{
	//Debug
	FMOD_RESULT fmodResult;

	//Channel Creation
	FMOD::Channel *fmodChannel = nullptr;
	fmodSystem->playSound(ResourceManager::GetSound(path), nullptr, isPaused, &fmodChannel);
	fmodChannel->setMode(FMOD_3D);
	
	//Audio source position
	FMOD_VECTOR sourcePosition = {positionX, positionY, 0};

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
	return true;
}

void AudioEngine::onDebugEvent(const OnDebugEventChanged* event)
{
	if (event->key == DebugPlaySound)
	{
		Instance()->loadSound("Sounds\\griddy.mp3", FMOD_3D);
		Instance()->playSound("Sounds\\griddy.mp3", false, 0.1f, 0, 0);

		Instance()->loadSound("Sounds\\doneit.mp3", FMOD_3D);
		//Instance()->playSound("Sounds\\doneit.mp3", false, 0.1f, 10, 10);
	}
}

void AudioEngine::updateListenerPositon(float positionX, float positionY) 
{
	listenerPosition = {positionX, positionY, 0};
}





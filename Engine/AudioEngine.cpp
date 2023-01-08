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

	//One listener (player)
	fmodSystem->set3DNumListeners(1);

	//Default factors
	fmodSystem->set3DSettings(1, 1, 1);

	Griddy::Events::subscribe(this, &AudioEngine::onDebugEvent);
	return true;
}

void AudioEngine::update() 
{ 
	//updateListenerPositon(0, 0);

	//Position of listenere
	listenerPosition = FMOD_VECTOR(0, 0, 0);
	
	//forward/up vectors left at default
	FMOD_VECTOR forward = FMOD_VECTOR(0, 0, 0);
	FMOD_VECTOR up = FMOD_VECTOR(0, 0, 0);

	//Set listener (player) position
	fmodSystem->set3DListenerAttributes(0, &listenerPosition, 0, &forward, &up);

	//System must be updated once per cycle
	fmodSystem->update(); 
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
	FMOD::Channel *fmodChannel = nullptr;
	fmodSystem->playSound(ResourceManager::GetSound(path), nullptr, isPaused, &fmodChannel);

	//Audio source position
	FMOD_VECTOR sourcePosition = {100000, 100000, 1000000};
	std::cout << "Source: " << sourcePosition.x << " " << sourcePosition.y << " " << sourcePosition.y << "\n";
	std::cout << "Listener: " << listenerPosition.x << " " << listenerPosition.y << " " << listenerPosition.y << "\n";

	//Set audio position
	fmodChannel->set3DAttributes(&sourcePosition, nullptr);

	//Set min/max falloff
	fmodChannel->set3DMinMaxDistance(1, 2);
	return true;
}

void AudioEngine::onDebugEvent(const OnDebugEventChanged* event)
{
	if (event->key == DebugPlaySound)
	{
		Instance()->loadSound("Sounds\\griddy.mp3", FMOD_DEFAULT);
		Instance()->playSound("Sounds\\griddy.mp3", false, 0.1f, 10000, 10000);

		Instance()->loadSound("Sounds\\doneit.mp3", FMOD_DEFAULT);
		Instance()->playSound("Sounds\\doneit.mp3", false, 0.1f, 100000, 10000);
	}
}

void AudioEngine::updateListenerPositon(float positionX, float positionY) 
{
	listenerPosition = FMOD_VECTOR(positionX, positionY, 0);
}





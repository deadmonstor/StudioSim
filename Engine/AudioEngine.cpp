#include "AudioEngine.h"

bool AudioEngine::init() 
{ 
	FMOD_RESULT fmodResult;
	FMOD::System *fmodSystem = NULL;

	fmodResult = FMOD::System_Create(&fmodSystem);

	if (fmodResult != FMOD_OK) 
	{
		LOG_ERROR("FMod failed to create the system");
		return false;
	}
	
	fmodResult = fmodSystem->init(512, FMOD_INIT_NORMAL, 0);
	if (fmodResult != FMOD_OK) 
	{
		LOG_ERROR("FMod failed to initialise the system");
		return false;
	}
}

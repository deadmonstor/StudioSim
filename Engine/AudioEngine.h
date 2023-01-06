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
};


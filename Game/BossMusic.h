#pragma once
#include "Util/SingletonTemplate.h"
#include <Util/Events/Events.h>
#include "GameEvents.h"


class BossMusic : public SingletonTemplate<BossMusic>
{
public:
	void Initialise();
private:
	void PlayMusic(EnterBossRoomEvent* event);
	void StopMusic(BossDeathEvent* event);
};


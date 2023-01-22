#pragma once
#include "Core/Component.h"
#include "Util/Events/EngineEvents.h"

class FireballComponent : public Component
{
public:
	void start() override;
	void update() override;

	void getDebugInfo(std::string*) override;
};

#pragma once
#include "Core/Component.h"
#include "Util/Events/EngineEvents.h"

class FireballComponent : public Component
{
	int8_t onAnimationEndedEventID = -1;
public:
	void start() override;
	void update() override;
	void lateUpdate() override;
	void destroy() override;
	void onAnimationEnded(OnAnimationEnded* event);

	void getDebugInfo(std::string*) override;
};

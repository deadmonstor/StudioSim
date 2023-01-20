#pragma once 

#include "Core/Component.h"
#include "Core/GameObject.h"
#include "Core/Components/AnimatedSpriteRenderer.h"
#include <Util/Events/EngineEvents.h>

class DestroyAfterAnimation : public Component
{
	int onAnimationEndedEventID = -1;

public:
	virtual void start() override;
	virtual void destroy() override;
	void onAnimationEnded(OnAnimationEnded* event);
};
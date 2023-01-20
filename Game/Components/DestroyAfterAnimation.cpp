#include "DestroyAfterAnimation.h"
#include "Core/SceneManager.h"
#include <Util/Events/Events.h>

void DestroyAfterAnimation::start()
{
	if (onAnimationEndedEventID == -1)
		onAnimationEndedEventID = Griddy::Events::subscribe(this, &DestroyAfterAnimation::onAnimationEnded);
}

void DestroyAfterAnimation::destroy()
{
	if (onAnimationEndedEventID != -1)
		Griddy::Events::unsubscribe(this, &DestroyAfterAnimation::onAnimationEnded, onAnimationEndedEventID);
}

void DestroyAfterAnimation::onAnimationEnded(OnAnimationEnded* event)
{
	if (event->animatedSpriteRenderer->getOwner() == getOwner())
	{
		SceneManager::Instance()->destroyGameObject(this->getOwner());
	}
}
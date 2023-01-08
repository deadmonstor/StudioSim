#include "AnimatedSpriteRenderer.h"

#include <utility>

#include "Core/GameObject.h"
#include "Util/Time.h"
#include "Util/Events/EngineEvents.h"
#include "Util/Events/Events.h"

AnimatedSpriteRenderer::AnimatedSpriteRenderer(std::vector<Texture> textureList, const double updateEveryXMS)
{
	this->textureList = std::move(textureList);
	this->updateEveryXMS = updateEveryXMS;
}

void AnimatedSpriteRenderer::update()
{
	if (lastUpdate > Time::getTime() - updateEveryXMS)
		return;

	if (textureList.empty())
		return;

	currentIndex++;

	if (textureList.size() <= currentIndex)
	{
		currentIndex = 0;
		Griddy::Events::invoke<OnAnimationEnded>(this);
		if (owner->isBeingDeleted()) return;
	}

	texture = textureList[currentIndex];
	lastUpdate = Time::getTime();

	SpriteRenderer::update();
}

void AnimatedSpriteRenderer::getDebugInfo(std::string* string)
{
	std::stringstream ss;
	ss << "Current Index: " << currentIndex << std::endl;
	ss << "Last Update: " << lastUpdate << std::endl;
	ss << "Update Every X MS: " << updateEveryXMS << std::endl;
	ss << "Texture List Size: " << textureList.size() << std::endl;
	string->append(ss.str());
	SpriteRenderer::getDebugInfo(string);
}

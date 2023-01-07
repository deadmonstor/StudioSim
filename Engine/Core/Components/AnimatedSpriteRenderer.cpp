#include "AnimatedSpriteRenderer.h"

#include <utility>
#include "Util/Time.h"

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
		currentIndex = 0;

	texture = textureList[currentIndex];
	lastUpdate = Time::getTime();

	SpriteRenderer::update();
}

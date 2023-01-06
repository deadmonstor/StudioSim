#include "AnimatedSpriteRenderer.h"
#include "Util/Time.h"

AnimatedSpriteRenderer::AnimatedSpriteRenderer(std::vector<Texture> textureList, float updateEveryXMS)
{ 
	this->textureList = textureList;
	this->updateEveryXMS = updateEveryXMS;
}

void AnimatedSpriteRenderer::update() 
{ 
	if (lastUpdate > (Time::getTime() - updateEveryXMS))
		return;
	
	if (textureList.size() == 0)
		return;

	currentIndex++;

	if (textureList.size() <= currentIndex)
		currentIndex = 0;

	texture = textureList[currentIndex];
	lastUpdate = Time::getTime();

	SpriteRenderer::update();
}


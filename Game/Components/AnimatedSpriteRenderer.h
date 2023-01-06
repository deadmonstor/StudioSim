#pragma once
#include "Core/Components/SpriteRenderer.h"
#include <vector>

class AnimatedSpriteRenderer : public SpriteRenderer
{
public:
	AnimatedSpriteRenderer(std::vector<Texture> textureList, float updateEveryXMS);

	std::vector<Texture> textureList;

	void update() override;
	int currentIndex = 0;
	float lastUpdate = 0;
	float updateEveryXMS = 0;
};
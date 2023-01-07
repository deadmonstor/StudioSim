#pragma once
#include <vector>
#include "Core/Components/SpriteRenderer.h"

class AnimatedSpriteRenderer : public SpriteRenderer
{
public:
	AnimatedSpriteRenderer(std::vector<Texture> textureList, double updateEveryXMS);

	std::vector<Texture> textureList;

	void update() override;
	unsigned long long currentIndex = 0;

	double lastUpdate = 0;
	double updateEveryXMS = 0;
};
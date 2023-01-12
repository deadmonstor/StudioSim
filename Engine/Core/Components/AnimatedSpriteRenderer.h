#pragma once
#include <vector>
#include "Core/Components/SpriteComponent.h"

class AnimatedSpriteRenderer : public SpriteComponent
{
private:
	int debugCurIndex = 0;
	double debugUpdateEverXMS = 0;
	float debugLastUpdate = 0;
	double debugTextureList = 0;
public:
	AnimatedSpriteRenderer(std::vector<Texture> textureList, double updateEveryXMS);
	bool doSpriteUpdate();

	std::vector<Texture> textureList;

	void update() override;
	void getDebugInfo(std::string*) override;
	unsigned long long currentIndex = 0;

	double lastUpdate = 0;
	double updateEveryXMS = 0;
};
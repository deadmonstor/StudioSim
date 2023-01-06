#pragma once
#include "Core/Components/AnimatedSpriteRenderer.h"
#include "Core/Components/SpriteRenderer.h"

class Tile final : public AnimatedSpriteRenderer
{
public:
	Tile(const std::vector<Texture> &textureList, float updateEveryXMS) :
		AnimatedSpriteRenderer(textureList, updateEveryXMS) {}
	void SetTexture(const Texture& texture);
	void SetShader(const Shader & shader);
};

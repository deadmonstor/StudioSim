﻿#pragma once
#include "Core/Components/AnimatedSpriteRenderer.h"
#include "Core/Components/SpriteComponent.h"

class Tile final : public AnimatedSpriteRenderer
{
public:
	Tile(const std::vector<Texture> &_textureList, const double _updateEveryXMS) :
		AnimatedSpriteRenderer(_textureList, _updateEveryXMS)
	{
		
	}
	
	void SetTexture(const Texture& texture);
	void SetShader(const Shader& shader);
};

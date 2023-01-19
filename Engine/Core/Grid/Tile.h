#pragma once
#include "Core/Components/SpriteComponent.h"

class Tile final : public SpriteComponent
{
public:
	Tile(const Texture& _texture)
	{
		SetTexture(_texture);
	}
	
	void SetTexture(const Texture& texture);
	void SetShader(const Shader& shader);
};

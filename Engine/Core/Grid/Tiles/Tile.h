#pragma once
#include "Core/Components/SpriteComponent.h"

struct TileHolder;

class Tile : public SpriteComponent
{
public:
	Tile(const Texture& _texture) : SpriteComponent()
	{
		SetTexture(_texture);
	}
	
	void SetTexture(const Texture& texture);
	void SetShader(const Shader& shader);

	void destroy() override;
	virtual void init(TileHolder* curTileHolder) {}
	virtual bool canInteractWith() { return false; }
	virtual void onInteractedWith(TileHolder* curTileHolder) {}
};

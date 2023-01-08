#include "Tile.h"

void Tile::SetTexture(const Texture& _texture)
{
	this->texture = _texture;
}

void Tile::SetShader(const Shader& _shader)
{
	this->setShader(_shader);
}

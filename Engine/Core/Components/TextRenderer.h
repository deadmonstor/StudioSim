#pragma once
#include "Util/SingletonTemplate.h"
#include "Core/Renderer/ResourceManager.h"
#include "Core/Renderer/Texture.h"
#include <ft2build.h>
#include FT_FREETYPE_H


class SpriteComponent;

class TextRenderer : public SingletonTemplate<TextRenderer>
{
public:
	void init();
	void renderText(std::string text, float screenPosX, float screenPosY, float scale, glm::vec3 colour, glm::vec2 pivot);
	glm::vec2 renderTextSize(std::string text, float scale);

private:
	FT_Library ft;
	FT_Face face;
	SpriteComponent* internalSpriteComponent;

	struct Char
	{
		Texture* texture;
		glm::ivec2 Size;
		glm::ivec2 Bearing;
		unsigned int Advance;
	};
	std::map<char, Char>Chars;

	unsigned int VAO, VBO;
};

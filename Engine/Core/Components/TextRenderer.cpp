#include <glad/glad.h>
#include "TextRenderer.h"

#include "SpriteComponent.h"
#include "Core/Renderer/Lighting.h"
#include "Util/Logger.h"

void TextRenderer::init()
{
	internalSpriteComponent = new SpriteComponent();
	internalSpriteComponent->setShader(ResourceManager::GetShader("textunlit"));
	
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	
	if (FT_Init_FreeType(&ft))
	{
		LOG_ERROR("Freetype did not intialise");
	}

	if (const auto errorCode = FT_New_Face(ft, "Fonts/AncientModernTales.ttf", 0, &face); errorCode != 0)
	{
		LOG_ERROR("Font did not load");
	}
	else
	{
		FT_Set_Pixel_Sizes(face, 0, 48);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		for(unsigned char c = 0; c < 128; c++)
		{
			if (FT_Load_Char(face, c, FT_LOAD_RENDER) != 0)
			{
				LOG_ERROR("Glyph " + std::to_string(c) + " could not be loaded");
				continue;
			}

			auto texture = new Texture();
			texture->Internal_Format = GL_RGBA;
			texture->Image_Format = GL_RGBA;
			texture->GenerateFont(face->glyph->bitmap.width, face->glyph->bitmap.rows, face->glyph->bitmap.buffer);

			Char currentChar =
			{
				texture,
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				static_cast<unsigned int>(face->glyph->advance.x)
			};
			Chars.insert(std::pair<char, Char>(c, currentChar));
		}
	}

	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}

void TextRenderer::renderText(std::string text, float screenPosX, const float screenPosY, const float scale, const glm::vec3 colour)
{
	internalSpriteComponent->getShader().SetVector3f("spriteColor", colour.x, colour.y, colour.z, true);
	Lighting::Instance()->refreshLightData(internalSpriteComponent, LightUpdateRequest::All);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);

	for (std::string::const_iterator c = text.begin(); c != text.end(); ++c)
	{
		const auto [texture, Size, Bearing, Advance] = Chars[*c];
		const float xPosition = screenPosX + Bearing.x * scale;
		const float yPosition = screenPosY - (Size.y - Bearing.y) * scale;

		const float width = Size.x * scale;
		const float height = Size.y * scale;

		const float vertices[6][4] =
		{
			{xPosition, yPosition + height, 0.0f, 0.0f},
			{xPosition, yPosition, 0.0f, 1.0f},
			{xPosition + width, yPosition, 1.0f, 1.0f},

			{xPosition, yPosition + height, 0.0f, 0.0f},
			{xPosition + width, yPosition, 1.0f, 1.0f},
			{xPosition + width, yPosition + height, 1.0f, 0.0f}
		};

		texture->Bind();
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		screenPosX += (Advance >> 6) * scale;
	}
	
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_BLEND);
}

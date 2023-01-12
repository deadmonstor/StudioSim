#include "TextRenderer.h"
#include "Util/Logger.h"


void TextRenderer::init()
{
	if (FT_Init_FreeType(&ft))
	{
		LOG_ERROR("Freetype did not intialise");
	}

	if (FT_New_Face(ft, "Fonts/AncientModernTales.ttf", 0, &face))
	{
		LOG_ERROR("Font did not load");
	}
	else
	{
		FT_Set_Pixel_Sizes(face, 0, 48);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		for(unsigned char c = 0; c < 128; c++)
		{
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				LOG_ERROR("Glyph " + std::to_string(c) + " could not be loaded");
				continue;
			}

			texture = new Texture();
			texture->Generate(face->glyph->bitmap.width, face->glyph->bitmap.rows, face->glyph->bitmap.buffer);

			Char currentChar =
			{
				texture->ID,
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				static_cast<unsigned int>(face->glyph->advance.x)
			};
			Chars.insert(std::pair<char, Char>(c, currentChar));
		}
		texture->Bind();
		//delete texture;
	}
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void TextRenderer::renderText(std::string text, float screenPosX, float screenPosY, float scale, glm::vec3 colour)
{
	ResourceManager::GetShader("text").Use();
	ResourceManager::GetShader("text").SetVector3f(("textColor"), colour.x, colour.y, colour.z);

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);

	for (std::string::const_iterator c = text.begin(); c != text.end(); c++)
	{
		Char currentChar = Chars[*c];
		float xPosition = screenPosX + currentChar.Bearing.x * scale;
		float yPosition = screenPosY - (currentChar.Size.y - currentChar.Bearing.y) * scale;

		float width = currentChar.Size.x * scale;
		float height = currentChar.Size.y * scale;

		float vertices[6][4] =
		{
			{xPosition, yPosition + height, 0.0f, 0.0f},
			{xPosition, yPosition, 0.0f, 1.0f},
			{xPosition + width, yPosition, 1.0f, 1.0f},

			{xPosition, yPosition + height, 0.0f, 0.0f},
			{xPosition + width, yPosition, 1.0f, 1.0f},
			{xPosition + width, yPosition + height, 1.0f, 0.0f}
		};

		glBindTexture(GL_TEXTURE_2D, currentChar.TextureID);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		screenPosX += (currentChar.Advance >> 6) * scale;
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

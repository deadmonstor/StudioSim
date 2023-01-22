#include <glad/glad.h>
#include "texture.h"

Texture::Texture()
	: Width(0),
	Height(0),
	Internal_Format(GL_RGB),
	Image_Format(GL_RGB),
	Wrap_S(GL_CLAMP_TO_EDGE),
	Wrap_T(GL_CLAMP_TO_EDGE),
	Filter_Min(GL_NEAREST),
	Filter_Max(GL_NEAREST)
{
	glGenTextures(1, &this->ID);
}

void Texture::Generate(const GLint width, const GLint height, const unsigned char* data)
{
	this->Width = width;
	this->Height = height;

	glBindTexture(GL_TEXTURE_2D, this->ID);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, this->Internal_Format, width, height, 0, this->Image_Format, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->Wrap_S);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->Wrap_T);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->Filter_Min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->Filter_Max);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::GenerateFont(const GLint width, const GLint height, const unsigned char* data)
{
	this->Width = width;
	this->Height = height;
	
	glBindTexture(GL_TEXTURE_2D, this->ID);
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RED,
		width,
		height,
		0,
		GL_RED,
		GL_UNSIGNED_BYTE,
		data
		);
	// set texture options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Bind() const
{
	glBindTexture(GL_TEXTURE_2D, this->ID);
}
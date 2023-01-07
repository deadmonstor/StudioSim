#pragma once


typedef int GLint;
class Texture
{
public:
	unsigned int ID {};
	GLint Width, Height;
	GLint Internal_Format;
	GLint Image_Format;

	GLint Wrap_S;
	GLint Wrap_T;
	GLint Filter_Min;
	GLint Filter_Max;
	
	Texture();
	void Generate(GLint width, GLint height, const unsigned char* data);
	void Bind() const;
};

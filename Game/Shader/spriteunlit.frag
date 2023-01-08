#version 330 core

uniform sampler2D image;
uniform vec3 spriteColor;

in vec2 TexCoords;
out vec4 color;

void main()
{
	color = vec4(spriteColor, 1.0) * texture(image, TexCoords);
}  
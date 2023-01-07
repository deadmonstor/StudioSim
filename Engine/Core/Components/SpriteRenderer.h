#pragma once
#include <Core/Renderer/texture.h>
#include "Core/Component.h"
#include "Core/Renderer/Shader.h"

class SpriteRenderer : public Component
{
public:
	~SpriteRenderer() override;
	void start() override;
	void createBuffers();
	void update() override;
	void lateUpdate() override;

	unsigned int quadVAO;
	Shader shader; 
	Texture texture;
	glm::vec3 color = glm::vec3(1.0f);
};

#pragma once
#include "Core/Component.h"
#include "Core/Renderer/shader.h"
#include "Core/Renderer/texture.h"

class SpriteRenderer final : public Component
{
public:
	~SpriteRenderer() override;
	void start() override;
	void update() override;
	void lateUpdate() override;
	void render() override;

	unsigned int quadVAO;
	Shader shader; 
	Texture texture;
	glm::vec3 color = glm::vec3(1.0f);
};

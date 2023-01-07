﻿#pragma once
#include <Core/Renderer/texture.h>
#include "Core/Component.h"
#include "Core/Renderer/Shader.h"

class SpriteRenderer : public Component
{
	glm::vec3 color = glm::vec3(1.0f);

public:
	~SpriteRenderer() override;
	
	void start() override;
	void createBuffers();
	void update() override;
	void lateUpdate() override;
	void getDebugInfo(std::string*) override;
	
	void setColor(glm::vec3 color);
	glm::vec3 getColor() const { return color; }

	unsigned int quadVAO;
	Shader shader; 
	Texture texture;
};

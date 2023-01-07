#include "SpriteRenderer.h"
#include <glad/glad.h>

#include "Core/Renderer/ResourceManager.h"
#include "Util/Events/EngineEvents.h"
#include "Util/Events/Events.h"

SpriteRenderer::~SpriteRenderer()
{
	Griddy::Events::invoke(new OnSpriteRendererComponentRemoved(this));
}

void SpriteRenderer::start()
{
	Component::start();
	createBuffers();
	
	Griddy::Events::invoke(new OnSpriteRendererComponentStarted(this));
}

void SpriteRenderer::createBuffers()
{
	unsigned int VBO;
	constexpr float vertices[] =
	{
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 
    
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &this->quadVAO);
	glGenBuffers(1, &VBO);
    
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(this->quadVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);  
	glBindVertexArray(0);

	shader = ResourceManager::GetShader("sprite");
}

void SpriteRenderer::update()
{
	Component::update();
}

void SpriteRenderer::lateUpdate()
{
	Component::lateUpdate();
}

void SpriteRenderer::setColor(const glm::vec3 color)
{
	this->color = color;
	shader.SetVector3f("spriteColor", color);
}

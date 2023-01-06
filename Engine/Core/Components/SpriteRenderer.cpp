#include "SpriteRenderer.h"
#include <glad/glad.h>
#include "Util/Events/EngineEvents.h"
#include "Util/Events/Events.h"

SpriteRenderer::~SpriteRenderer()
{
	Griddy::Events::Instance()->invoke(new OnSpriteRendererComponentRemoved(this));
}

void SpriteRenderer::start()
{
	Component::start();
	createBuffers();
	
	Griddy::Events::Instance()->invoke(new OnSpriteRendererComponentStarted(this));
}

void SpriteRenderer::createBuffers()
{
	// configure VAO/VBO
	unsigned int VBO;
	float vertices[] = { 
		// pos      // tex
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
}

void SpriteRenderer::update()
{
	Component::update();
}

void SpriteRenderer::lateUpdate()
{
	Component::lateUpdate();
}

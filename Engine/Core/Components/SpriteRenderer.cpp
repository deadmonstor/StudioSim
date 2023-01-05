#include "SpriteRenderer.h"

#include "Library/glm/ext.hpp"
#include "Library/glm/glm.hpp"

SpriteRenderer::~SpriteRenderer() = default;

void SpriteRenderer::start()
{
	Component::start();

	unsigned int VBO;
	float vertices[] = { 
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 
    
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};
}

void SpriteRenderer::update()
{
	Component::update();
}

void SpriteRenderer::lateUpdate()
{
	Component::lateUpdate();
}

void SpriteRenderer::render()
{
	Component::render();

	//this->shader.Use();
	glm::vec2 position {1, 2};
	glm::vec2 size {1, 3};
	
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0f));  

	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); 
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f)); 
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

	model = glm::scale(model, glm::vec3(size, 1.0f));
  
	/*this->shader.SetMatrix4("model", model);
	this->shader.SetVector3f("spriteColor", color);
  
	glActiveTexture(GL_TEXTURE0);
	texture.Bind();*/
}

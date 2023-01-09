#include "SpriteRenderer.h"
#include <glad/glad.h>

#include "Core/Renderer/ResourceManager.h"
#include "Util/Events/RenderEvents.h"
#include "Util/Events/Events.h"

SpriteRenderer::~SpriteRenderer()
{
	Component::~Component();
	Griddy::Events::invoke<OnSpriteRendererComponentRemoved>(this);
}

void SpriteRenderer::start()
{
	Component::start();
	createBuffers();
	
	Griddy::Events::invoke<OnSpriteRendererComponentStarted>(this);
}

void SpriteRenderer::createBuffers()
{
	if (shader.ID == 0)
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

void SpriteRenderer::getDebugInfo(std::string* string)
{
	std::stringstream ss;
	ss << "Texture: " << texture.ID << std::endl;
	ss << "Color: " << color.r << ", " << color.g << ", " << color.b << std::endl;
	ss << "Shader ID: " << shader.ID << std::endl;
	string->append(ss.str());
	
	Component::getDebugInfo(string);
}

void SpriteRenderer::setColor(const glm::vec3 color)
{
	this->color = color;
	shader.SetVector3f("spriteColor", color);
}

Shader SpriteRenderer::getShader() const
{
	return shader;
}

void SpriteRenderer::setShader(const Shader shader)
{
	this->shader = shader;
}

void SpriteRenderer::setLit(const bool lit)
{
	setShader(ResourceManager::GetShader(lit ? "sprite" : "spriteunlit"));
}

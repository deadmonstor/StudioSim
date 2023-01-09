#include "SpriteComponent.h"

#include "Core/Renderer/ResourceManager.h"
#include "Util/Events/Events.h"
#include "Util/Events/RenderEvents.h"

SpriteComponent::~SpriteComponent()
{
	Component::~Component();
	Griddy::Events::invoke<OnSpriteRendererComponentRemoved>(this);
}

void SpriteComponent::start()
{
	Component::start();
	createBuffers();
	
	Griddy::Events::invoke<OnSpriteRendererComponentStarted>(this);
}

void SpriteComponent::createBuffers()
{
	if (shader.ID == 0)
		shader = ResourceManager::GetShader("sprite");
}

void SpriteComponent::update()
{
	Component::update();
}

void SpriteComponent::lateUpdate()
{
	Component::lateUpdate();
}

void SpriteComponent::getDebugInfo(std::string* string)
{
	std::stringstream ss;
	ss << "Texture: " << texture.ID << std::endl;
	ss << "Color: " << color.r << ", " << color.g << ", " << color.b << std::endl;
	ss << "Shader ID: " << shader.ID << std::endl;
	string->append(ss.str());
	
	Component::getDebugInfo(string);
}

void SpriteComponent::setColor(const glm::vec3 color)
{
	this->color = color;
	shader.SetVector3f("spriteColor", color, true);
}

Shader SpriteComponent::getShader() const
{
	return shader;
}

void SpriteComponent::setShader(const Shader shader)
{
	this->shader = shader;
}

void SpriteComponent::setLit(const bool lit)
{
	setShader(ResourceManager::GetShader(lit ? "sprite" : "spriteunlit"));
}

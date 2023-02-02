#include "Panel.h"
#include "Core/Components/Transform.h"
#include "Core/Renderer/ResourceManager.h"

Panel::Panel() : SpriteComponent()
{
	transform = new Transform();
	setShader(ResourceManager::GetShader("spriteunlit"));
}

void Panel::render()
{
	Renderer::Instance()->renderUI(this,
		transform->getPosition(),
		transform->getScale(),
		transform->getRotation());
}

void Panel::SetTexture(const Texture& texture)
{
	this->setTexture(texture);
}

void Panel::SetShader(const Shader& shader)
{
	this->setShader(shader);
}

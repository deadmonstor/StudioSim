#include "ButtonComponent.h"
#include "Util/Events/EngineEvents.h"
#include "Util/Events/Events.h"
#include "Core/Components/AnimatedSpriteRenderer.h"
#include "Core/Input.h"

void ButtonComponent::render()
{
	Renderer::Instance()->renderSprite(this,
		pos,
		size,
		0);
}

void ButtonComponent::onMouseDown(const OnMouseDown* event)
{
	//check if mouse is in bounds of button
	const glm::vec2 mousePos = Input::getMousePosition();
	if (mousePos.x >= pos.x && mousePos.x <= pos.x + size.x &&
		mousePos.y >= pos.y && mousePos.y <= pos.y + size.y)
	{
		onClick();
	}
}

void ButtonComponent::onClick()
{
	std::cout << "Button Doing Something\n" << std::endl;
}

void ButtonComponent::SetTexture(const Texture& texture)
{
	this->setTexture(texture);
}

void ButtonComponent::SetShader(const Shader& shader)
{
	this->setShader(shader);
}

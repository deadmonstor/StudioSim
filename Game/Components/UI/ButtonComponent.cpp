#include "ButtonComponent.h"
#include "Core/Input.h"
#include "Core/Components/AnimatedSpriteRenderer.h"
#include "Util/Events/EngineEvents.h"
#include "Util/Events/Events.h"

ButtonComponent::ButtonComponent(const Texture& _texture): Panel()
{
	if (eventID == -1)
		eventID = Griddy::Events::subscribe(this, &ButtonComponent::onMouseDown);
	
	SetTexture(_texture);
}

void ButtonComponent::render()
{
	Panel::render();	

	if (getColor() != glm::vec3(1.0f))
	{
		setColor({1, 1, 1});
	}
}

void ButtonComponent::destroy()
{
	Panel::destroy();

	if (eventID != -1)
		Griddy::Events::unsubscribe(this, &ButtonComponent::onMouseDown, eventID);
}

void ButtonComponent::onMouseDown(const OnMouseDown* event)
{
	const Transform* transform = getTransform();
	if (transform == nullptr) return;
	
	glm::vec2 pos = transform->getPosition() * Renderer::Instance()->getAspectRatio();
	const glm::vec2 size = transform->getScale() * Renderer::Instance()->getAspectRatio();
	const glm::vec2 pivot = getPivot();
	
	pos = pos + glm::vec2(-pivot.x * size.x, -pivot.y * size.y);
	
	const glm::vec2 mousePos = Input::getMousePositionScreenSpace();
	/*
		std::cout << "Button Pos X: " << pos.x << " Button PosY: " << pos.y << std::endl;
		std::cout << "Button Size X: " << size.x << " Button Size Y: " << size.y << std::endl;
		std::cout << "Mouse Pos X: " << mousePos.x << " Mouse PosY: " << mousePos.y << std::endl;
	*/

	if (mousePos.x >= pos.x && mousePos.x <= pos.x + size.x  &&
		mousePos.y >= pos.y && mousePos.y <= pos.y + size.y)
	{
		onClick();
	}
}

void ButtonComponent::onClick()
{
	setColor({1, 0, 0});
}
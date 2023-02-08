#include "ButtonComponent.h"
#include "Core/Input.h"
#include "Core/Components/AnimatedSpriteRenderer.h"
#include "Util/Events/EngineEvents.h"
#include "Util/Events/Events.h"
#include "Core/AudioEngine.h"

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

void ButtonComponent::update()
{
	if(isMouseInButton())
		setColor({ 0.5, 0.5, 0.5 });
}

void ButtonComponent::onMouseDown(const OnMouseDown* event)
{
	if (isMouseInButton())
		onClick();
}

bool ButtonComponent::isMouseInButton()
{
	const Transform* transform = getTransform();
	if (transform == nullptr) return false;

	glm::vec2 pos = transform->getPosition();
	const glm::vec2 size = transform->getScale();
	const glm::vec2 pivot = getPivot();

	pos = pos + glm::vec2(-pivot.x * size.x, -pivot.y * size.y);

	const glm::vec2 mousePos = Input::getMousePositionScreenSpace();

	if (mousePos.x >= pos.x && mousePos.x <= pos.x + size.x &&
		mousePos.y >= pos.y && mousePos.y <= pos.y + size.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ButtonComponent::onClick()
{
	AudioEngine::Instance()->playSound("Sounds\\Click.wav", false, 0.2f, 0, 0, AudioType::SoundEffect);
	setColor({1, 0, 0});
}
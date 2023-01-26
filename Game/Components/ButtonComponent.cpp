#include "ButtonComponent.h"
#include "Util/Events/EngineEvents.h"
#include "Util/Events/Events.h"
#include "Core/Components/AnimatedSpriteRenderer.h"

void ButtonComponent::onMouseDown(const OnMouseDown* event)
{
	//check if mouse is in bounds of button
	onClick();
}

void ButtonComponent::onClick()
{

}

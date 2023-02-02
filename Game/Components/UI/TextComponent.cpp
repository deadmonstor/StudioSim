#include "TextComponent.h"
#include "Core/Components/TextRenderer.h"
#include "Core/Components/Transform.h"

void TextComponent::render()
{
	const auto transform = getTransform();
	
	TextRenderer::Instance()->renderText(text,
		transform->getPosition().x,
		transform->getPosition().y,
		1 ,
		{1, 1, 1},
		getPivot());
}

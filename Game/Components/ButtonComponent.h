#pragma once
#include "Core/Component.h"
#include "Core/Components/SpriteComponent.h"
#include "Core/Renderer/Texture.h"
#include "Util/Events/EngineEvents.h"
#include "Util/Events/Events.h"

//Example Class Replace As Parent Class Later To Create Multiple Buttons
class ButtonComponent final : public SpriteComponent
{
public:
	ButtonComponent(const Texture& _texture) : SpriteComponent()
	{
		Griddy::Events::subscribe(this, &ButtonComponent::onMouseDown);
		SetTexture(_texture);
	}

	void SetTexture(const Texture& texture);
	void SetShader(const Shader& shader);

	void onMouseDown(const OnMouseDown* event);
	void onClick();
protected:
	//Text 
	std::string buttonText;

	//Sprite
	SpriteComponent* buttonSprite;

	//Sizes for Render/Check If Mouse Over
	int sizeX, sizeY, posX, posY;
};


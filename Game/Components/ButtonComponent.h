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


	void render();
	void SetTexture(const Texture& texture);
	void SetShader(const Shader& shader);

	void onMouseDown(const OnMouseDown* event);
	void onClick();

	void setSize(const glm::vec2& buttSize)
	{
		size = buttSize;
	}

	glm::vec2 getSize()
	{
		return size;
	}

	void setPos(const glm::vec2& buttPos)
	{
		pos = buttPos;
	}

	glm::vec2 getPos()
	{
		return pos;
	}
protected:
	//Text 
	std::string buttonText;

	//Sizes for Render/Check If Mouse Over
	glm::vec2 pos, size;
};


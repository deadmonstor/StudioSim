#pragma once
#include "Core/Component.h"
#include "Util/Events/EngineEvents.h"

//Example Class Replace As Parent Class Later To Create Multiple Buttons
class ButtonComponent : public Component
{
public:
	void start() override;
	void update() override;
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


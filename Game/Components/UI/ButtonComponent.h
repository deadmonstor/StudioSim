#pragma once
#include "Core/Components/UI/Panel.h"
#include "Core/Renderer/Texture.h"
#include "Util/Events/EngineEvents.h"
#include "Util/Events/Events.h"

class ButtonComponent : public Panel
{
public:
	ButtonComponent(const Texture& _texture);

	void render() override;
	void destroy() override;
	void onMouseDown(const OnMouseDown* event);
	virtual void onClick();
protected:
	//Text 
	std::string buttonText;

	int eventID = -1;
};


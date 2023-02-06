#pragma once
#include "Core/Components/UI/Panel.h"

class TextComponent final : public Panel
{
public:
	TextComponent() = default;

	void render() override;
	void setText(const std::string& _text) { text = _text; }
	void setScale(const float _size) { size = _size; }
protected:
	//Text 
	std::string text;
	float size = 1;
};


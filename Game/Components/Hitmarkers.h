#pragma once
#include "Core/Component.h"
#include "Core/Components/SpriteComponent.h"

struct HitmarkerInfo
{
	std::string text;
	double time;
	glm::vec2 pos;
};

class Hitmarkers : public Component
{
	SpriteComponent* spriteComponent;
	int onEngineRenderID = -1;

	std::vector<HitmarkerInfo> hitmarkerTexts;
	
public:
	void onEngineRender(OnEngineRender* event);
	void start() override;
	void update() override;
	void destroy() override;

	void addHitmarker(const std::string text, const double time = 1.0, const glm::vec2 pos = { 0,0 });
};

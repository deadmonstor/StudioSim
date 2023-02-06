#pragma once
#include "Core/Component.h"
#include "Core/Components/SpriteComponent.h"

struct HitmarkerInfo
{
	std::string text;
	glm::vec2 pos;
	glm::vec3 color;
	double time;
	glm::vec2 direction;
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

	void addHitmarker(std::string text, double time = 1.0, glm::vec2 pos = { 0,0 }, glm::vec3 color = { 1,1,1 });
};

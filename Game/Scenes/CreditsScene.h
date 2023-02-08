#pragma once
#include "Core/Scene.h"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "Util/Events/EngineEvents.h"

class CreditsScene : public Scene
{
	int engineRenderID = -1;
	
	void renderText(glm::vec2 worldPosition, const std::string& text, float scale, const glm::vec3& color);
	void renderTextOutlined(glm::vec2 worldPosition, const std::string& text, float scale, float outlineThickness, const glm::vec3& color, const glm::vec3& colorOutline);
public:
    void init() override;
    void update() override;
	void onEngineRender(const OnEngineRender* event);
    void destroy() override;

	inline static bool hasCompletedTutorialLevel = false;
};

#include "Hitmarkers.h"

#include "Core/Components/TextRenderer.h"
#include "Core/Components/Transform.h"
#include "Util/Time.h"
#include "Util/Events/Events.h"

void Hitmarkers::onEngineRender(OnEngineRender* event)
{
	for (auto& [text, pos, color, time, direction] : hitmarkerTexts)
	{
		const auto screenSpace = pos - Renderer::Instance()->getCameraPosScreenSpace();
		const glm::vec2 size = TextRenderer::Instance()->renderTextSize(text, 0.4f);

		TextRenderer::Instance()->renderText(
			" " + text,
			screenSpace.x - size.x / 2,
			screenSpace.y - size.y,
			0.4f,
			color,
			{ 0,0 });

		time -= Time::getDeltaTime();
		pos = pos + glm::vec2{direction.x * Time::getDeltaTime(), direction.y * Time::getDeltaTime()};
	}
}

void Hitmarkers::start()
{
	Component::start();
	
	if (onEngineRenderID == -1)
		onEngineRenderID = Griddy::Events::subscribe(this, &Hitmarkers::onEngineRender);
}

void Hitmarkers::update()
{
	Component::update();
	
	std::erase_if(
		hitmarkerTexts,
		[](const HitmarkerInfo& info) { return info.time <= 0; });
}

void Hitmarkers::destroy()
{
	Component::destroy();
	
	if (onEngineRenderID != -1)
		Griddy::Events::unsubscribe(this, &Hitmarkers::onEngineRender, onEngineRenderID);
}

void Hitmarkers::addHitmarker(const std::string text, const double time, const glm::vec2 pos, const glm::vec3 color, const int randomAmount)
{
	// add random value to pos to make it look more natural
	const auto random = [](const float min, const float max) { return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min))); };
	const auto randomPos = glm::vec2(random(-randomAmount, randomAmount), random(-randomAmount, randomAmount));
	auto randomDirection =  glm::vec2(random(-1, 1), random(-1, 1));

	randomDirection.x = 50 * randomDirection.x;
	randomDirection.y = 50 * randomDirection.y;
	
	hitmarkerTexts.push_back({ text, pos + randomPos, color, time, randomDirection});
}

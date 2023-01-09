#include "Lighting.h"

#include <algorithm>

#include "Input.h"
#include "Renderer.h"
#include "Core/Components/SpriteComponent.h"
#include "glm/common.hpp"
#include "Util/Time.h"

void Lighting::addToLightQueue(const OnLightComponentStarted* event)
{
	lightRenderQueue.push_back(event->light);
	refreshLightData(LightUpdateRequest::All);
}

void Lighting::removeFromLightQueue(const OnLightComponentRemoved* event)
{
	lightRenderQueue.erase(std::ranges::remove(lightRenderQueue, event->light).begin(), lightRenderQueue.end());
	refreshLightData(LightUpdateRequest::All);
}

static std::vector<LightName> lightIDToName {}; 

void Lighting::doLight(SpriteComponent* spriteRenderer,
						int& i,
						const glm::vec2& position,
						const glm::vec4& lightColorBase,
						const glm::vec3& falloff,
						const LightUpdateRequest lightUpdateRequest) const
{
	const auto windowSize = Renderer::getWindowSize();
	
	glm::vec2 lightPos = position;
	lightPos.x = lightPos.x / windowSize.x;
	lightPos.y = lightPos.y / windowSize.y * -1 + 1;

	glm::vec4 lightColor = lightColorBase;

	if (debugLightColor)
	{
		const auto base_value = Time::getTime();

		const auto r = 0.5 * (sin(base_value - 2)	    + 1);
		const auto g = 0.5 * (sin(base_value + 2)	    + 1);
		const auto b = 0.5 * (sin(base_value      )	    + 1);
	
		lightColor = glm::vec4(r,g,b, 0.5f);
	}

	if (const auto size = lightIDToName.size(); size <= i)
	{
		const std::string id = std::to_string(i);
		const std::string pos = "uLightsPos[" + id + "]";
		const std::string light_color = "uLightColor[" + id + "]";
		const std::string light_fallout = "uFalloff[" + id + "]";
		
		const LightName lightNameStruct =
		{
			pos.c_str(), 
			light_color.c_str(), 
			light_fallout.c_str()
		};
		
		lightIDToName.insert(lightIDToName.end(), lightNameStruct);
	}

	spriteRenderer->getShader().Use();
	
	if (showMouseLight || static_cast<bool>(lightUpdateRequest & LightUpdateRequest::Position))
		spriteRenderer->getShader().SetVector3f(lightIDToName[i].pos, glm::vec3(lightPos, 0.1f));
	
	if (debugLightColor || static_cast<bool>(lightUpdateRequest & LightUpdateRequest::Color))
		spriteRenderer->getShader().SetVector4f(lightIDToName[i].color, lightColor);

	if (static_cast<bool>(lightUpdateRequest & LightUpdateRequest::Falloff))
		spriteRenderer->getShader().SetVector3f(lightIDToName[i].falloff, falloff);

	i += 1;
}

void Lighting::refreshLightData(const LightUpdateRequest lightUpdateRequest) const
{
	for(const auto& spriteRenderer : Renderer::Instance()->spriteRenderQueue)
	{
		refreshLightData(spriteRenderer, lightUpdateRequest);
	}
}

void Lighting::refreshLightData(SpriteComponent* spriteRenderer, const LightUpdateRequest lightUpdateRequest) const
{
	int i = 0;
	if (showMouseLight)
	{
		doLight(spriteRenderer,
			i,
			Input::getMousePosition(),
			{1.0f, 0.75f, 0.3f, 1.0f},
			{0.4f, 3.0f, 20.0f}, lightUpdateRequest);	
	}
	
	for (const Light* light : lightRenderQueue)
	{
		auto lightPosition = light->getOwner()->getTransform()->GetPosition();
		
		doLight(spriteRenderer,
			i,
			lightPosition,
			light->getColor(),
			light->getFalloff() , lightUpdateRequest);	
	}
	
	spriteRenderer->getShader().SetInteger("uLightCount", glm::clamp(i, 0, 100));
}

void Lighting::onDebugEvent(const OnDebugEventChanged* event)
{
	if (event->key == DebugMouseLight)
		showMouseLight = !showMouseLight;

	if (event->key == DebugLightColor)
		debugLightColor = !debugLightColor;
	
	refreshLightData(LightUpdateRequest::All);
}

void Lighting::init()
{
	Griddy::Events::subscribe(this, &Lighting::addToLightQueue);
	Griddy::Events::subscribe(this, &Lighting::removeFromLightQueue);
	Griddy::Events::subscribe(this, &Lighting::onDebugEvent);
}

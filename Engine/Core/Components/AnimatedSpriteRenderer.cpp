#include "AnimatedSpriteRenderer.h"

#include "Core/GameObject.h"
#include "glm/common.hpp"
#include "Util/Time.h"
#include "Util/Events/EngineEvents.h"
#include "Util/Events/Events.h"

AnimatedSpriteRenderer::AnimatedSpriteRenderer(std::vector<Texture> textureList, const double updateEveryXMS)
{
	this->textureList = std::move(textureList);
	this->updateEveryXMS = updateEveryXMS;

	debugCurIndex = currentIndex;
	debugUpdateEverXMS = updateEveryXMS;
	debugLastUpdate = 0;
	debugTextureList = this->textureList.size();
}

void AnimatedSpriteRenderer::doTextureUpdate()
{
	setTexture(textureList[currentIndex]);
	lastUpdate = Time::getTime();
	debugLastUpdate = lastUpdate;
}

bool AnimatedSpriteRenderer::doSpriteUpdate()
{
	// TODO: When we are really lagging this should "skip" frames
	if (lastUpdate > Time::getTime() - updateEveryXMS)
		return true;

	if (textureList.empty())
		return true;

	currentIndex++;
	debugCurIndex = currentIndex;

	if (textureList.size() <= currentIndex)
	{
		currentIndex = 0;
		debugCurIndex = currentIndex;
		doTextureUpdate();
		Griddy::Events::invoke<OnAnimationEnded>(this);
	}

	doTextureUpdate();
	return false;
}

void AnimatedSpriteRenderer::update()
{
	SpriteComponent::update();
	doSpriteUpdate();
}

void AnimatedSpriteRenderer::lateUpdate()
{
	if (debugCurIndex != currentIndex)
	{
		currentIndex = glm::clamp(debugCurIndex, 0, static_cast<int>(textureList.size()) - 1);
		debugCurIndex = currentIndex;
		doTextureUpdate();
	}

	if (updateEveryXMS != 0.0)
		updateEveryXMS = debugUpdateEverXMS;

	SpriteComponent::lateUpdate();
}

void AnimatedSpriteRenderer::getDebugInfo(std::string* string)
{
	ImGui::Indent();
	ImGui::InputInt("Cur Index", &debugCurIndex);
	ImGui::InputFloat("Last Updated", &debugLastUpdate);
	ImGui::InputDouble("Update Every X MS", &debugUpdateEverXMS, 0.01, 1.0, "%.3f");
	ImGui::InputDouble("Texture List Size", &debugTextureList);
	ImGui::Unindent();
	
	SpriteComponent::getDebugInfo(string);
}

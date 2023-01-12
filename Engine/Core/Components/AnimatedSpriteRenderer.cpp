#include "AnimatedSpriteRenderer.h"

#include "Core/GameObject.h"
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
	
	doSpriteUpdate();
}

bool AnimatedSpriteRenderer::doSpriteUpdate()
{
	if (lastUpdate > Time::getTime() - updateEveryXMS)
		return true;

	if (textureList.empty())
		return true;

	currentIndex++;

	if (textureList.size() <= currentIndex)
	{
		currentIndex = 0;
		Griddy::Events::invoke<OnAnimationEnded>(this);
		if (getOwner() == nullptr || getOwner()->isBeingDeleted()) return true;
	}

	setTexture(textureList[currentIndex]);
	lastUpdate = Time::getTime();
	return false;
}

void AnimatedSpriteRenderer::update()
{
	if (doSpriteUpdate()) return;
	SpriteComponent::update();

	if (updateEveryXMS != 0.0)
		updateEveryXMS = debugUpdateEverXMS;
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

#include "AnimatedSpriteRenderer.h"

#include "Core/GameObject.h"
#include "Util/Time.h"
#include "Util/Events/EngineEvents.h"
#include "Util/Events/Events.h"

AnimatedSpriteRenderer::AnimatedSpriteRenderer(std::vector<Texture> textureList, const double updateEveryXMS)
{
	this->textureList = std::move(textureList);
	this->updateEveryXMS = updateEveryXMS;
}

void AnimatedSpriteRenderer::update()
{
	if (lastUpdate > Time::getTime() - updateEveryXMS)
		return;

	if (textureList.empty())
		return;

	currentIndex++;

	if (textureList.size() <= currentIndex)
	{
		currentIndex = 0;
		Griddy::Events::invoke<OnAnimationEnded>(this);
		if (getOwner() == nullptr || getOwner()->isBeingDeleted()) return;
	}

	setTexture(textureList[currentIndex]);
	lastUpdate = Time::getTime();

	SpriteComponent::update();
}

void AnimatedSpriteRenderer::getDebugInfo(std::string* string)
{
	ImGui::Indent();
	ImGui::TextUnformatted("Current Index: ");
	auto id = new int(currentIndex);
	ImGui::InputInt("", id);

	ImGui::TextUnformatted("Last Updated: ");
	id = new int(lastUpdate);
	ImGui::InputInt("", id);
	
	ImGui::TextUnformatted("Update Every X MS: ");
	id = new int(updateEveryXMS);
	ImGui::InputInt("", id);

	ImGui::TextUnformatted("Texture List Size: ");
	id = new int(textureList.size());
	ImGui::InputInt("", id);
	ImGui::Unindent();
	
	SpriteComponent::getDebugInfo(string);
}

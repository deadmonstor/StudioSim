#include "FireballComponent.h"

#include <vector>

#include "Core/Component.h"
#include "Core/GameObject.h"
#include "Core/Components/AnimatedSpriteRenderer.h"
#include "Core/Components/Light.h"
#include "Core/Components/Transform.h"
#include "Core/Renderer/ResourceManager.h"
#include "Util/Time.h"
#include "Util/Events/Events.h"

void FireballComponent::start()
{
	Component::start();

	const std::vector textureListFireball = ResourceManager::GetTexturesContaining("Fireball");
	owner->addComponent<AnimatedSpriteRenderer>(textureListFireball, 0.1f);
	owner->addComponent<Light>();

	Griddy::Events::subscribe(this, &FireballComponent::onAnimationEnded);
}

void FireballComponent::update()
{
	Component::update();

	// move the fireball to the right
	owner->getTransform()->SetPosition(owner->getTransform()->GetPosition() + glm::vec2{ 200.0f, 0.0f } * static_cast<float>(Time::getDeltaTime()));
}

void FireballComponent::lateUpdate()
{
	Component::lateUpdate();
}

void FireballComponent::onAnimationEnded(OnAnimationEnded* event)
{
	if (event->animatedSpriteRenderer->owner == owner)
	{
		SceneManager::Instance()->destroyGameObject(this->owner);
	}
}

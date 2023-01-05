#include "SceneManager.h"

#include "Components/SpriteRenderer.h"
#include "Components/Transform.h"

bool SceneManager::changeScene(const std::string& scene)
{
	LOG_INFO("Changed scene to " + scene);
	currentScene = new Scene();
	
	return true;
}

bool SceneManager::init()
{
	return changeScene("scene stuff");
}

GameObject* SceneManager::createGameObject(const glm::vec2 position)
{
	const auto created = new GameObject();

	const auto transform = new Transform();
	created->addComponent(transform);
	transform->SetPosition(position);
	
	created->addComponent(new SpriteRenderer());
	created->start();
	
	currentScene->gameObjects.push_back(created);
	if (currentScene->gameObjects.size() > 100000)
	{
		LOG_ERROR("Somehow we have more than 100000 gameobjects, lets stop");
	}

	created->isInitialized = true;
	return created;
}

void SceneManager::update() const
{
	for(auto i : currentScene->gameObjects)
	{
		i->update();
	}
}

void SceneManager::render() const
{
	for(auto i : currentScene->gameObjects)
	{
		i->render();
	}
}

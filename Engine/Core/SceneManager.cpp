#include "SceneManager.h"

#include "Components/SpriteRenderer.h"
#include "Components/TestComponent.h"

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

GameObject* SceneManager::createGameObject()
{
	const auto created = new GameObject();
	created->addComponent(new TestComponent());
	created->addComponent(new SpriteRenderer());
	created->start();

	currentScene->gameObjects.push_back(created);
	if (currentScene->gameObjects.size() > 100000)
	{
		LOG_ERROR("Somehow we have more than 100000 gameobjects, lets stop");
	}
	
	return created;
}

void SceneManager::update()
{
	for(auto i : currentScene->gameObjects)
	{
		i->update();
	}
}

void SceneManager::render()
{
	for(auto i : currentScene->gameObjects)
	{
		i->render();
	}
}

#include "SceneManager.h"

#include "Components/TestComponent.h"

bool SceneManager::changeScene(const std::string& scene)
{
	// Something something something it failed for some reason kekw
	LOG_INFO("Changed scene to " + scene);
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
	created->start();

	gameObjects.push_back(created);
	if (gameObjects.size() > 100000)
	{
		//LOG_ERROR("Somehow we have more than 100000 gameobjects, lets stop");
	}
	
	return created;
}

void SceneManager::update()
{
	for(auto i : gameObjects)
	{
		i->update();
	}
}

void SceneManager::render()
{
	for(auto i : gameObjects)
	{
		i->render();
	}
}

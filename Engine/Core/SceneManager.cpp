#include "SceneManager.h"

#include "Components/AnimatedSpriteRenderer.h"
#include "Components/Transform.h"
#include "Renderer/Renderer.h"
#include "Util/Events/EngineEvents.h"
#include "Util/Events/Events.h"

void SceneManager::destroyScene(const Scene* scene)
{
	Renderer::Instance()->SetCamera(nullptr);
	
	const auto gameObjects = scene->gameObjects;
	for(const auto object : gameObjects)
	{
		destroyGameObject(object);
	}
}

bool SceneManager::changeScene(const std::string& scene)
{
	if (currentScene != nullptr)
	{
		destroyScene(currentScene);
	}
	
	LOG_INFO("Changed scene to " + scene);
	currentScene = new Scene();

	Griddy::Events::invoke<OnSceneChanged>(scene);
	return true;
}

bool SceneManager::init()
{
	Griddy::Events::subscribe(this, &SceneManager::onSceneChanged);
	return changeScene("renderScene");
}

GameObject* SceneManager::createGameObject(const std::string name, const glm::vec2 position)
{
	const auto created = new GameObject();
	created->transform = new Transform();
	created->transform->name = "Transform";
	created->name = name;
	
	created->addComponent(created->transform);
	created->transform->SetPosition(position);
	created->start();
	
	currentScene->gameObjects.push_back(created);
	if (currentScene->gameObjects.size() > 100000)
	{
		LOG_ERROR("Somehow we have more than 100000 gameobjects, lets stop");
	}

	created->isInitialized = true;
	return created;
}

void SceneManager::destroyGameObject(GameObject* gameObject) const
{
	gameObject->beingDeleted = true;
}

void SceneManager::update() const
{
	for(auto i : currentScene->gameObjects)
	{
		i->update();
	}
}

void SceneManager::lateUpdate() const
{
	for (auto i : currentScene->gameObjects)
	{
		i->lateUpdate();
	}

	for (auto i : currentScene->gameObjects)
	{
		if (i->beingDeleted)
		{
			currentScene->gameObjects.erase(std::ranges::remove(currentScene->gameObjects, i).begin(), currentScene->gameObjects.end());
			delete i;
		}
	}
}


void SceneManager::render() const
{
	
}

void SceneManager::onSceneChanged(const OnSceneChangeRequested* event)
{
	changeScene(event->key);
}

#include "SceneManager.h"

#include "Components/AnimatedSpriteRenderer.h"
#include "Components/Transform.h"
#include "Renderer/Renderer.h"
#include "Util/Events/EngineEvents.h"
#include "Util/Events/Events.h"

void SceneManager::destroyScene(const Scene* scene)
{
	shuttingDown = true;

	for(const auto gameObjects = scene->gameObjects; const auto object : gameObjects)
	{
		destroyGameObject(object);
	}

	Renderer::Instance()->setCamera(nullptr);
	deleteAllPendingObjects();
}

bool SceneManager::changeScene(const std::string& scene)
{
	if (isLoadingScene()) return false;
	
	loadingScene = true;
	if (currentScene != nullptr)
	{
		LOG_INFO("Destroy current scene " + currentScene->name);
		destroyScene(currentScene);
	}

	shuttingDown = false;
	LOG_INFO("Changed scene to " + scene);
	currentScene = new Scene();
	currentScene->name = scene;

	Griddy::Events::invoke<OnSceneChanged>(scene);
	loadingScene = false;
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
	created->transform->setName("Transform");
	created->name = name;
	
	created->addComponent(created->transform);
	created->transform->setPosition(position);
	created->start();
	
	currentScene->gameObjects.push_back(created);
	if (currentScene->gameObjects.size() > 100000)
	{
		LOG_ERROR("Somehow we have more than 100000 gameobjects, lets stop");
	}

	if constexpr (_DEBUG_ECS)
	{
		LOG_INFO("Created game object " + name);
	}
	
	created->isInitialized = true;
	return created;
}

void SceneManager::destroyGameObject(GameObject* gameObject) const
{
	gameObject->beingDeleted = true;
	gameObject->destroy();

	if constexpr (_DEBUG_ECS)
	{
		LOG_INFO("Removing game object " + gameObject->getName());
	}
}

void SceneManager::update() const
{
	for(auto i : currentScene->gameObjects)
	{
		i->update();
	}
}

void SceneManager::deleteAllPendingObjects() const
{
	for(auto i = currentScene->gameObjects.begin(); i != currentScene->gameObjects.end();)
	{
		if ((*i)->beingDeleted)
		{
			delete *i;
			i = currentScene->gameObjects.erase(i);
		}
		else
		{
			++i;
		}
	}
}

void SceneManager::lateUpdate() const
{
	for (auto i : currentScene->gameObjects)
	{
		i->lateUpdate();
	}

	deleteAllPendingObjects();
}


void SceneManager::render() const
{
	
}

void SceneManager::onSceneChanged(const OnSceneChangeRequested* event)
{
	changeScene(event->key);
}

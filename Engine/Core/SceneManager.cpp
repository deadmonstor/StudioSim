#include "SceneManager.h"

#include "Components/AnimatedSpriteRenderer.h"
#include "Components/Transform.h"
#include "Renderer/Renderer.h"
#include "Util/Events/EngineEvents.h"
#include "Util/Events/Events.h"

void SceneManager::destroyScene(const Scene* scene)
{
	#ifdef _DEBUG_ECS
		LOG_INFO("destroyScene() ");
	#endif
	
	shuttingDown = true;

	for(const auto gameObjects = scene->gameObjects; const auto object : gameObjects)
	{
		destroyGameObject(object);
	}

	addPendingObjects();
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
	
	pendingObjects.push_back(created);
	
	#ifdef _DEBUG_ECS
		LOG_INFO("Created game object " + name);
	#endif
	
	return created;
}

void SceneManager::addPendingObjects()
{
	for (const auto object : pendingObjects)
	{
		addGameObject(object);
	}
	
	pendingObjects.clear();
}

void SceneManager::addGameObject(GameObject* gameObject)
{
	currentScene->gameObjects.push_back(gameObject);
	gameObject->isInitialized = true;
	gameObject->start();
	
	if (currentScene->gameObjects.size() > 100000)
	{
		#ifdef _DEBUG_ECS
			LOG_ERROR("Somehow we have more than 100000 gameobjects, lets stop");
		#endif
	}
}

void SceneManager::destroyGameObject(GameObject* gameObject) const
{
	if (gameObject->isBeingDeleted())
	{
		return;
	}

	#ifdef _DEBUG_ECS
		LOG_INFO("Removing game object " + gameObject->getName());
	#endif
	
	gameObject->beingDeleted = true;
	gameObject->destroy();
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
	#ifdef _DEBUG_ECS
		bool hasDeletedSomething = false;
	#endif
	
	for(auto i = currentScene->gameObjects.begin(); i != currentScene->gameObjects.end();)
	{
		if ((*i)->beingDeleted)
		{
			#ifdef _DEBUG_ECS
				hasDeletedSomething = true;
			#endif
			
			delete *i;
			i = currentScene->gameObjects.erase(i);
		}
		else
		{
			++i;
		}
	}

	#ifdef _DEBUG_ECS
		if (hasDeletedSomething)
			LOG_INFO("deleteAllPendingObjects() ");
	#endif
}

void SceneManager::lateUpdate()
{
	for (auto i : currentScene->gameObjects)
	{
		i->lateUpdate();
	}

	Renderer::Instance()->sortRenderQueue();
	deleteAllPendingObjects();
	addPendingObjects();
}


void SceneManager::render() const
{
	
}

void SceneManager::onSceneChanged(const OnSceneChangeRequested* event)
{
	changeScene(event->key);
}

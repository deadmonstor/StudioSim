#pragma once
#include <string>

#include "GameObject.h"
#include "Scene.h"
#include "glm/vec2.hpp"
#include "Util/Logger.h"
#include "Util/SingletonTemplate.h"
#include "Util/Events/EngineEvents.h"

class SceneManager : public SingletonTemplate<SceneManager>
{
public:
	void destroyScene(const Scene* scene);
	bool changeScene(const std::string& scene);
	bool init();
	GameObject* createGameObject(const ::std::string name, glm::vec2 position);
	void destroyGameObject(GameObject* gameObject) const;

	void update() const;
	void deleteAllPendingObjects() const;
	void lateUpdate() const;
	void render() const;

	Scene* currentScene;
	void onSceneChanged(const OnSceneChangeRequested* event);
private:
	friend class ImGuiHandler;
};

#pragma once
#include <string>

#include "GameObject.h"
#include "Scene.h"
#include "glm/vec2.hpp"
#include "Util/Logger.h"
#include "Util/SingletonTemplate.h"

class SceneManager : public SingletonTemplate<SceneManager>
{
public:
	bool changeScene(const std::string& scene);
	bool init();
	GameObject* createGameObject(const ::std::string name, glm::vec2 position);
	void destroyGameObject(const GameObject* gameObject) const;

	void update() const;
	void lateUpdate() const;
	void render() const;

	Scene* currentScene;
private:
	friend class ImGuiHandler;
};

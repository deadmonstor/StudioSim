#pragma once
#include <string>

#include "GameObject.h"
#include "Scene.h"
#include "Util/Logger.h"
#include "Util/SingletonTemplate.h"

class SceneManager : public SingletonTemplate<SceneManager>
{
public:
	bool changeScene(const std::string& scene);
	bool init();
	GameObject* createGameObject();

	void update();
	void render();

	Scene* currentScene;
};

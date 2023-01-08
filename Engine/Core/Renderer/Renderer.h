#pragma once
#include <list>
#include <string>

#include "Core/GameObject.h"
#include "Core/Components/Camera.h"
#include "Core/Components/Light.h"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "Util/SingletonTemplate.h"
#include "Util/Events/RenderEvents.h"

class SpriteRenderer;
struct GLFWwindow;
class Renderer : public SingletonTemplate<Renderer>
{
	GLFWwindow* window = nullptr;
	Camera* mainCam = nullptr;
	glm::vec2 windowSize = { 1, 1 };
	std::list<SpriteRenderer*> spriteRenderQueue;

	friend class Lighting;
public:
	static GLFWwindow* getWindow() { return Instance()->window; }
	static glm::vec2 getWindowSize() { return Instance()->windowSize; }

	[[nodiscard]] glm::vec2 getCameraPos() const;
	void setCamera(Camera* cam) { mainCam = cam; }
	[[nodiscard]] Camera* getCamera() const { return mainCam; }
	
	void setWindowSize(glm::ivec2);
	void setWindowTitle(const std::string& title) const;
	bool createWindow(const std::string &windowName);
	void renderSprite(SpriteRenderer* spriteRenderer, glm::vec2 position, glm::vec2 size, float rotation) const;
	
	void cleanup() const;
	void render();
	void init();

	void addToRenderQueue(const OnSpriteRendererComponentStarted*);
	void removeFromRenderQueue(const OnSpriteRendererComponentRemoved*);
};

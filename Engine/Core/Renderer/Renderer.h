#pragma once
#include <list>
#include <string>

#include "Core/GameObject.h"
#include "Core/Components/Camera.h"
#include "Core/Components/Transform.h"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "Util/SingletonTemplate.h"

class OnSpriteRendererComponentRemoved;
class OnSpriteRendererComponentStarted;
class SpriteRenderer;

struct GLFWwindow;
class Renderer : public SingletonTemplate<Renderer>
{
	GLFWwindow* window = nullptr;
	glm::vec2 windowSize = { 1, 1 };
	Camera* mainCam = nullptr;
	
public:
	static GLFWwindow* GetWindow() { return Instance()->window; }
	static glm::vec2 GetWindowSize() { return Instance()->windowSize; }

	[[nodiscard]] glm::vec2 GetCameraPos() const
	{
		if (!mainCam || !mainCam->owner )
			return {0, 0};
		
		return mainCam->owner->getTransform()->position - GetWindowSize() / 2.f;
	}
	void SetCamera(Camera* cam) { mainCam = cam; }
	[[nodiscard]] Camera* GetCamera() const { return mainCam; }
	
	// TODO: Change this to vector when we have it
	void SetWindowSize(glm::ivec2);
	void SetWindowTitle(const std::string& title) const;
	bool createWindow(const std::string &windowName);
	void renderSprite(SpriteRenderer* spriteRenderer, glm::vec2 position, glm::vec2 scale, float rotation) const;
	void cleanup() const;
	void render();
	void init();

	void addToRenderQueue(const OnSpriteRendererComponentStarted* OnSpriteRendererComponentStartedEvent);
	void removeFromRenderQueue(const OnSpriteRendererComponentRemoved* OnSpriteRendererComponentRemovedEvent);
	std::list<SpriteRenderer*> renderQueue;
};

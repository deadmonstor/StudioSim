#pragma once
#include <list>
#include <string>

#include "Core/GameObject.h"
#include "Core/Components/Camera.h"
#include "Core/Components/Light.h"
#include "Core/Components/Transform.h"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "Util/SingletonTemplate.h"
#include "Util/Events/EngineEvents.h"

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
	void renderSprite(SpriteRenderer* spriteRenderer, glm::vec2 position, glm::vec2 size, float rotation) const;
	void cleanup() const;
	void render();
	void init();

	void addToRenderQueue(const OnSpriteRendererComponentStarted*);
	void removeFromRenderQueue(const OnSpriteRendererComponentRemoved*);
	void addToLightQueue(const OnLightComponentStarted*);
	void removeFromLightQueue(const OnLightComponentRemoved*);
	void onDebugEvent(const OnDebugEventChanged* event);

	std::list<SpriteRenderer*> spriteRenderQueue;
	std::list<Light*> lightRenderQueue;
};

#pragma once
#include <string>
#include <list>

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "Util/SingletonTemplate.h"

class OnSpriteRendererComponentRemoved;
class OnSpriteRendererComponentStarted;
class SpriteRenderer;
class GameObject;

struct GLFWwindow;
class Renderer : public SingletonTemplate<Renderer>
{
	GLFWwindow* window = nullptr;
	glm::vec2 windowSize;
	
public:
	static GLFWwindow* GetWindow() { return Instance()->window; }
	static glm::vec2 GetWindowSize() { return Instance()->windowSize; }
	
	// TODO: Change this to vector when we have it
	void SetWindowSize(glm::ivec2);
	void SetWindowTitle(const std::string& title) const;
	bool createWindow(const std::string &windowName);
	void renderSprite(SpriteRenderer* spriteRenderer, glm::vec2 position, glm::vec2 scale, float rotation);
	void cleanup() const;
	void render();
	void init();

	void addToRenderQueue(const OnSpriteRendererComponentStarted* OnSpriteRendererComponentStartedEvent);
	void removeFromRenderQueue(const OnSpriteRendererComponentRemoved* OnSpriteRendererComponentRemovedEvent);
	std::list<SpriteRenderer*> renderQueue;
};

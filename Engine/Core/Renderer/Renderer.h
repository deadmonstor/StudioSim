#pragma once
#include <string>

#include "SortingLayer.h"
#include "Core/GameObject.h"
#include "Core/Components/Camera.h"
#include "Core/Components/Light.h"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "Util/SingletonTemplate.h"
#include "Util/Events/RenderEvents.h"

class SortingLayer;
class SpriteComponent;
struct GLFWwindow;

inline const std::string& defaultSortingLayer = "DefaultLayer";

class Renderer : public SingletonTemplate<Renderer>
{
	GLFWwindow* window = nullptr;
	Camera* mainCam = nullptr;
	glm::vec2 windowSize = { 1, 1 };
	std::vector<SpriteComponent*> spriteRenderQueue;

	std::map<std::string, SortingLayer*> sortingLayers
	{
		{defaultSortingLayer, new SortingLayer(defaultSortingLayer, 0)}
	};
	
	friend class Lighting;
	friend class ImGuiHandler;
	void createVBOs();
	unsigned int quadVAO;
public:
	static GLFWwindow* getWindow() { return Instance()->window; }
	static glm::vec2 getWindowSize() { return Instance()->windowSize; }

	[[nodiscard]] glm::vec2 getCameraPos() const;
	void setCamera(Camera* cam) { mainCam = cam; }
	[[nodiscard]] Camera* getCamera() const { return mainCam; }
	
	void setWindowSize(glm::ivec2);
	void setWindowTitle(const std::string& title) const;
	bool createWindow(const std::string &windowName);
	void renderSprite(SpriteComponent* spriteRenderer, glm::vec2 position, glm::vec2 size, float rotation) const;
	
	void cleanup() const;
	void render();
	void init();

	void addToRenderQueue(const OnSpriteRendererComponentStarted*);
	void removeFromRenderQueue(const OnSpriteRendererComponentRemoved*);

	static SortingLayer& getDefaultSortingLayer();
	static SortingLayer& getSortingLayer(const std::string& layerName);
	static SortingLayer& addSortingLayer(const std::string& layerName, const int order);
	static void removeSortingLayer(const std::string& layerName);
	void sortRenderQueue();
};

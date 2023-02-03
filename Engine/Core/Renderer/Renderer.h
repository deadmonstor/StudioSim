#pragma once
#include <string>

#include "SortingLayer.h"
#include "texture.h"
#include "Core/GameObject.h"
#include "Core/Components/Camera.h"
#include "Core/Components/Light.h"
#include "glm/fwd.hpp"
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
	
	void createVBOs();
	void setupCommonShader(const std::string& name, glm::ivec2 value, glm::mat4 projection, glm::mat4 view);
	unsigned int quadVAO;
	
	friend class Lighting;
	friend class ImGuiHandler;
public:
	static GLFWwindow* getWindow() { return Instance()->window; }
	static glm::vec2 getWindowSize() { return Instance()->windowSize; }
	
	[[nodiscard]] glm::mat4 getViewProjectMatrix() const { return mainCam->getViewProjectMatrix(); }
	[[nodiscard]] glm::mat4 getProjectMatrix() const { return mainCam->getProjectMatrix(); }
	void getModelMatrix(glm::vec2 position, glm::vec2 size, float rotation, glm::vec2 pivot, glm::mat4& model);
	
	[[nodiscard]] unsigned int getCameraSize() const { return mainCam->getSize(); }
	[[nodiscard]] float getAspectRatio() const { return mainCam->getAspectRatio(); }
	[[nodiscard]] glm::vec2 getCameraPos() const;
	[[nodiscard]] glm::vec2 getCameraPosScreenSpace() const;
	[[nodiscard]] Camera* getCamera() const { return mainCam; }
	void setCamera(Camera* cam)
	{
		mainCam = cam;

		if (mainCam)
		{
			resetShaders();
		}
	}
	
	void setWindowSize(glm::ivec2);
	void resetShaders();
	void setWindowTitle(const std::string& title) const;
	bool createWindow(const std::string &windowName);
	void renderSprite(SpriteComponent* spriteRenderer, glm::vec2 position, glm::vec2 size, float rotation);
	void renderUI(SpriteComponent* spriteRenderer, glm::vec2 position, glm::vec2 size, float rotation);
	
	void cleanup() const;
	void render();
	void init();

	void addToRenderQueue(const OnSpriteRendererComponentStarted*);
	void removeFromRenderQueue(const OnSpriteRendererComponentRemoved*);
	void setWindowIcon(const std::string& icon);

	static SortingLayer& getDefaultSortingLayer();
	static SortingLayer& getSortingLayer(const std::string& layerName);
	static SortingLayer& addSortingLayer(const std::string& layerName, const int order);
	static void removeSortingLayer(const std::string& layerName);
	void sortRenderQueue();
};

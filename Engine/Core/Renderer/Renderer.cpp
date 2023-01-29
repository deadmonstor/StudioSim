#include <glad/glad.h>
#include "Renderer.h"
#include <Windows.h>

#include "Core/Input.h"
#include "Lighting.h"
#include "ResourceManager.h"
#include "SortingLayer.h"
#include "Core/GameObject.h"
#include "Core/Components/AnimatedSpriteRenderer.h"
#include "Core/Components/Transform.h"
#include "glm/gtx/transform.hpp"
#include "Util/Logger.h"
#include "Util/Time.h"
#include "Util/Events/Events.h"

void error_callback(const int error, const char *msg)
{
	const std::string s = "GLFW: [" + std::to_string(error) + "] " + msg + '\n';
	LOG_ERROR(s);
}

void framebuffer_size_callback(GLFWwindow* window, const int width, const int height)
{
	glViewport(0, 0, width, height);
	Renderer::Instance()->setWindowSize({width, height});
}

void Renderer::setWindowTitle(const std::string& title) const
{
	if (window == nullptr)
	{
		LOG_ERROR("Failed to set window title");
		return;
	}

	glfwSetWindowTitle(window, title.c_str());
}

void Renderer::createVBOs()
{
	unsigned int VBO;
	constexpr float vertices[] =
{
		0.0f, 1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 0.0f, 1.0f,

		0.0f, 1.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 1.0f, 1.0f
	};

	glGenVertexArrays(1, &this->quadVAO);
	glGenBuffers(1, &VBO);
    
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(this->quadVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);  
	glBindVertexArray(0);
}

glm::vec2 Renderer::getCameraPos() const
{
	if (mainCam == nullptr  || mainCam->getOwner() == nullptr || !mainCam->getOwner()->isValidTransform() )
		return {0, 0};
		
	return mainCam->getOwner()->getTransform()->getPosition();
}

glm::vec2 Renderer::getCameraPosScreenSpace() const
{
	// TODO: Fix these MAGIC numbers again
	if (mainCam == nullptr  || mainCam->getOwner() == nullptr || !mainCam->getOwner()->isValidTransform() )
		return {-(1080 / 2), -(600 / 2)};
		
	// TODO: Fix these MAGIC numbers again
	return mainCam->getOwner()->getTransform()->getPosition() + glm::vec2{-(1080 / 2), -(600 / 2)};
}

void Renderer::setupCommonShader(const std::string& name, const glm::ivec2 value, const glm::mat4 projection, const glm::mat4 view)
{
	LOG_INFO("Setting up common shader for " + name);

	Shader shader = ResourceManager::GetShader(name);

	shader.Use();
	shader.SetInteger("image", 0);
	shader.SetVector2f("Resolution", {value.x, value.y});
	shader.SetVector4f("AmbientColor", Lighting::Instance()->getAmbientColor());
	shader.SetMatrix4("uProjectionMatrix", projection);
}

void Renderer::setWindowSize(const glm::ivec2 value)
{
	if (window == nullptr)
	{
		LOG_ERROR("Failed to set window size");
		return;
	}
	
	windowSize = value;
	
	LOG_INFO("Window size set to " + std::to_string(value.x) + "x" + std::to_string(value.y));

	if (!ResourceManager::HasShader("sprite"))
		ResourceManager::LoadShader("Shader/sprite.vs", "Shader/sprite.frag", nullptr, "sprite");
	if (!ResourceManager::HasShader("spriteunlit"))
		ResourceManager::LoadShader("Shader/spriteunlit.vs", "Shader/spriteunlit.frag", nullptr, "spriteunlit");
	
	if (!ResourceManager::HasShader("text"))
		ResourceManager::LoadShader("Shader/textlit.vs", "Shader/textlit.frag", nullptr, "text");
	if (!ResourceManager::HasShader("textunlit"))
		ResourceManager::LoadShader("Shader/textunlit.vs", "Shader/textunlit.frag", nullptr, "textunlit");

	resetShaders();
	glfwSetWindowSize(window, value.x, value.y);
}

void Renderer::resetShaders()
{
	if (mainCam == nullptr)
		return;

	LOG_INFO("Resetting shaders");
	
	mainCam->screenSizeChanged();
	
	const glm::mat4 projectionMatrix = mainCam->getProjectMatrix();
	const glm::mat4 viewProjectionMatrix = mainCam->getViewProjectMatrix();
	const glm::vec2 value = getWindowSize();
	
	setupCommonShader("sprite", value, projectionMatrix, viewProjectionMatrix);
	setupCommonShader("spriteunlit", value, projectionMatrix, viewProjectionMatrix);
	setupCommonShader("text", value, projectionMatrix, viewProjectionMatrix);
	setupCommonShader("textunlit", value, projectionMatrix, viewProjectionMatrix);
}

bool Renderer::createWindow(const std::string &windowName)
{
	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
	{
		LOG_ERROR("Failed to create init GLFW");
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	window = glfwCreateWindow(1920, 1080, windowName.c_str(), nullptr, nullptr);
	if (window == nullptr)
	{
		LOG_ERROR("Failed to create GLFW window");
		return false;
	}
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		LOG_ERROR("Failed to initialize GLAD");
		return false;
	}

	setWindowSize({1920, 1080});
	
	return true;
}

void Renderer::cleanup() const
{
	if (window != nullptr)
	{
		glfwDestroyWindow(window);
	}
}

void Renderer::render()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (SpriteComponent* spriteRenderer : spriteRenderQueue)
	{
		const Transform* transform = spriteRenderer->getOwner()->getTransform();
		renderSprite(spriteRenderer, transform->getPosition(), transform->getScale(), transform->getRotation());
	}
	
	glDisable(GL_BLEND);
}

void Renderer::getModelMatrix(const glm::vec2 position, const glm::vec2 size, const float rotation, const glm::vec2 pivot, glm::mat4& model)
{
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0f));  
	model = glm::translate(model, glm::vec3(-pivot.x * size.x, -pivot.y * size.y, 0.0f));  

	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); 
	model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f)); 
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

	model = glm::scale(model, glm::vec3(size, 1.0f));
}

void Renderer::renderSprite(SpriteComponent* spriteRenderer, const glm::vec2 position, const glm::vec2 size, const float rotation)
{
	if (mainCam == nullptr)
		return;

	if (!mainCam->isInFrustum(position, size))
	{
		spriteRenderer->wasInFrame = false;
		return;
	}

	const glm::vec2 pivot = spriteRenderer->getPivot();
	Lighting::Instance()->refreshLightData(spriteRenderer, LightUpdateRequest::Position);

	spriteRenderer->getShader().SetVector3f("spriteColor", spriteRenderer->getColor(), true);
	glm::mat4 model;
	getModelMatrix(position, size, rotation, pivot, model);
	spriteRenderer->getShader().SetMatrix4("uModelMatrix", model, true);
	spriteRenderer->getShader().SetMatrix4("uProjectionMatrix", mainCam->getViewProjectMatrix(), true);
	
	glActiveTexture(GL_TEXTURE0);
	spriteRenderer->getTexture().Bind();
	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	spriteRenderer->wasInFrame = true;
}

void Renderer::renderUI(SpriteComponent* spriteRenderer, const glm::vec2 position, const glm::vec2 size, const float rotation)
{
	if (mainCam == nullptr)
		return;

	const glm::vec2 pivot = spriteRenderer->getPivot();
	
	spriteRenderer->getShader().SetVector3f("spriteColor", spriteRenderer->getColor(), true);
	glm::mat4 model;

	// TODO: This is probably wrong (position - camera position)
	getModelMatrix(position + getCameraPosScreenSpace(), size, rotation, pivot, model);
	spriteRenderer->getShader().SetMatrix4("uModelMatrix", model, true);
	spriteRenderer->getShader().SetMatrix4("uProjectionMatrix", mainCam->getViewProjectMatrix(), true);
	
	glActiveTexture(GL_TEXTURE0);
	spriteRenderer->getTexture().Bind();
	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void Renderer::init()
{
	Griddy::Events::subscribe(this, &Renderer::addToRenderQueue);
	Griddy::Events::subscribe(this, &Renderer::removeFromRenderQueue);

	createVBOs();
}

void Renderer::addToRenderQueue(const OnSpriteRendererComponentStarted* event)
{
	event->spriteRenderer->getShader().SetVector3f("spriteColor", event->spriteRenderer->getColor(), true);
	
	spriteRenderQueue.push_back(event->spriteRenderer);
	Lighting::Instance()->refreshLightData(event->spriteRenderer, LightUpdateRequest::All);
}

void Renderer::removeFromRenderQueue(const OnSpriteRendererComponentRemoved* event)
{
	spriteRenderQueue.erase(std::ranges::remove(spriteRenderQueue, event->spriteRenderer).begin(), spriteRenderQueue.end());
	Lighting::Instance()->refreshLightData(event->spriteRenderer, LightUpdateRequest::All);
}

void Renderer::sortRenderQueue()
{
	std::sort(spriteRenderQueue.begin(), spriteRenderQueue.begin() + static_cast<long long>(spriteRenderQueue.size()),
	[this](const SpriteComponent* x, const SpriteComponent* y) noexcept -> bool
	{
		if (x->getSortingLayer().getName() == y->getSortingLayer().getName())
		{
			return x->getSortingOrder() < y->getSortingOrder();
		}
		
		return x->getSortingLayer().getOrder() < y->getSortingLayer().getOrder();
	});
}

SortingLayer& Renderer::getDefaultSortingLayer()
{
	return *Instance()->sortingLayers[defaultSortingLayer];
}

SortingLayer& Renderer::getSortingLayer(const std::string& layerName)
{
	if (Instance()->sortingLayers.contains(layerName))
	{
		return *Instance()->sortingLayers[layerName];
	}
	
	LOG_WARNING("Tried to get SortingLayer (name: " + layerName + ") but it did not exist. Using default sorting layer instead.");
	return getDefaultSortingLayer();
}

SortingLayer& Renderer::addSortingLayer(const std::string& layerName, const int order)
{
	Instance()->sortingLayers[layerName] = new SortingLayer(layerName, order);
	return *Instance()->sortingLayers[layerName];
}

void Renderer::removeSortingLayer(const std::string& layerName)
{
	Instance()->sortingLayers.erase(layerName);
}
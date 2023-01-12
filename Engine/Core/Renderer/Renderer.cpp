#include <glad/glad.h>
#include "Renderer.h"
#include <Windows.h>

#include "Input.h"
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
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 
    
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
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
		
	return mainCam->getOwner()->getTransform()->position - getWindowSize() / 2.f;
}

void Renderer::setWindowSize(const glm::ivec2 value)
{
	if (window == nullptr)
	{
		LOG_ERROR("Failed to set window size");
		return;
	}
	
	windowSize = value;
	
	const glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(value.x), 
											static_cast<float>(value.y), 0.0f, -1.0f, 1.0f);

	ResourceManager::LoadShader("Shader/textunlit.vs", "Shader/textunlit.frag", nullptr, "text");
	ResourceManager::GetShader("text").SetMatrix4("projection", glm::mat4(projection));

	ResourceManager::GetShader("sprite").Use().SetMatrix4("projection", projection);
	ResourceManager::GetShader("sprite").SetVector2f("Resolution", {value.x, value.y});
	
	ResourceManager::GetShader("spriteunlit").Use().SetMatrix4("projection", projection);
	ResourceManager::GetShader("text").Use().SetMatrix4("projection", projection);
	ResourceManager::GetShader("textunlit").Use().SetMatrix4("projection", projection);
	
	glfwSetWindowSize(window, value.x, value.y);
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

	window = glfwCreateWindow(1, 1, windowName.c_str(), nullptr, nullptr);
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
	


	ResourceManager::LoadShader("Shader/sprite.vs", "Shader/sprite.frag", nullptr, "sprite");
	ResourceManager::GetShader("sprite").SetInteger("image", 0, true);
	ResourceManager::GetShader("sprite").SetInteger("normals", 1);
	ResourceManager::GetShader("sprite").SetVector4f("AmbientColor", {0.6f, 0.6f, 1.0f, 0.1f});
	
	ResourceManager::LoadShader("Shader/spriteunlit.vs", "Shader/spriteunlit.frag", nullptr, "spriteunlit");
	ResourceManager::GetShader("spriteunlit").SetInteger("image", 0, true);
	
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
	glClearColor(0, 0, 0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (SpriteComponent* spriteRenderer : spriteRenderQueue)
	{
		const Transform* transform = spriteRenderer->getOwner()->getTransform();
		renderSprite(spriteRenderer, transform->GetPosition(), transform->GetScale(), transform->GetRotation());
	}
	
	glDisable(GL_BLEND);
}

void Renderer::renderSprite(SpriteComponent* spriteRenderer, const glm::vec2 position, const glm::vec2 size, const float rotation) const
{
	if (position.x + size.x < 0 || position.x > windowSize.x || position.y + size.y < 0 || position.y > windowSize.y)
	{
		return;
	}
	
	Lighting::Instance()->refreshLightData(spriteRenderer, LightUpdateRequest::Position);

	spriteRenderer->getShader().Use();
	spriteRenderer->getShader().SetVector3f("spriteColor", spriteRenderer->getColor(), true);
	auto model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0f));  

	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); 
	model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f)); 
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

	model = glm::scale(model, glm::vec3(size, 1.0f)); 
  
	spriteRenderer->getShader().SetMatrix4("model", model, true);

	glActiveTexture(GL_TEXTURE1);
	spriteRenderer->getNormals().Bind();
	
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
	sortRenderQueue();
	Lighting::Instance()->refreshLightData(event->spriteRenderer, LightUpdateRequest::All);
}

void Renderer::removeFromRenderQueue(const OnSpriteRendererComponentRemoved* event)
{
	spriteRenderQueue.erase(std::ranges::remove(spriteRenderQueue, event->spriteRenderer).begin(), spriteRenderQueue.end());
	Lighting::Instance()->refreshLightData(event->spriteRenderer, LightUpdateRequest::All);
}

void Renderer::sortRenderQueue()
{
	// BUG : Is this slow?
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
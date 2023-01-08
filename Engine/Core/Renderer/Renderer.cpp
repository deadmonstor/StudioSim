#include <glad/glad.h>
#include "Renderer.h"
#include <Windows.h>

#include "Input.h"
#include "ResourceManager.h"
#include "Core/GameObject.h"
#include "Core/Components/AnimatedSpriteRenderer.h"
#include "Core/Components/Transform.h"
#include "glm/gtx/transform.hpp"
#include "Util/Logger.h"
#include "Util/Time.h"
#include "Util/Events/EngineEvents.h"
#include "Util/Events/Events.h"

void error_callback(const int error, const char *msg)
{
	const std::string s = "GLFW: [" + std::to_string(error) + "] " + msg + '\n';
	LOG_ERROR(s);
}

void framebuffer_size_callback(GLFWwindow* window, const int width, const int height)
{
	glViewport(0, 0, width, height);
	Renderer::Instance()->SetWindowSize({width, height});
}

void Renderer::SetWindowTitle(const std::string& title) const
{
	if (window == nullptr)
	{
		LOG_ERROR("Failed to set window title");
		return;
	}

	glfwSetWindowTitle(window, title.c_str());
}

void Renderer::SetWindowSize(const glm::ivec2 value)
{
	if (window == nullptr)
	{
		LOG_ERROR("Failed to set window size");
		return;
	}
	
	windowSize = value;
	
	const glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(value.x), 
											static_cast<float>(value.y), 0.0f, -1.0f, 1.0f);

	ResourceManager::GetShader("sprite").Use().SetMatrix4("projection", projection);
	ResourceManager::GetShader("sprite").SetVector2f("Resolution", {value.x, value.y});
	
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
	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").SetInteger("u_normals", 1);
	ResourceManager::GetShader("sprite").SetVector4f("AmbientColor", {0.6f, 0.6f, 1.0f, 0.05f});
	
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
	glClearColor(0,0,0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (SpriteRenderer* spriteRenderer : spriteRenderQueue)
	{
		const Transform* transform = spriteRenderer->owner->getTransform();
		renderSprite(spriteRenderer, transform->GetPosition(), transform->GetScale(), transform->GetRotation());
	}
	
	glDisable(GL_BLEND);
}

static bool showMouseLight = false;
static bool debugLightColor = false;

struct LightName
{
	LightName(const char* _pos, const char* _color, const char* _falloff)
	{
		auto res = new char[strlen(_pos)+1];
		strcpy_s(res, strlen(_pos)+1, _pos);
		pos = res;

		res = new char[strlen(_color)+1];
		strcpy_s(res, strlen(_color)+1, _color);
		color = res;

		res = new char[strlen(_falloff)+1];
		strcpy_s(res, strlen(_falloff)+1, _falloff);
		falloff = res;
	}

	char* pos;
	char* color;
	char* falloff;
};

static std::vector<LightName> lightIDToName {}; 

void Renderer::DoLight(SpriteRenderer* spriteRenderer, int& i, const glm::vec2& position, const glm::vec4& lightColorBase, const glm::vec3& falloff) const
{
	glm::vec2 lightPos = position;
	lightPos.x = lightPos.x / windowSize.x;
	lightPos.y = lightPos.y / windowSize.y * -1 + 1;

	glm::vec4 lightColor = lightColorBase;

	if (debugLightColor)
	{
		const auto base_value = Time::getTime();

		const auto r = 0.5 * (sin(base_value - 2)	    + 1);
		const auto g = 0.5 * (sin(base_value + 2)	    + 1);
		const auto b = 0.5 * (sin(base_value      )	    + 1);
	
		lightColor = glm::vec4(r,g,b, 0.5f);
	}

	if (const auto size = lightIDToName.size(); size <= i)
	{
		const std::string id = std::to_string(i);
		const std::string pos = "uLightsPos[" + id + "]";
		const std::string light_color = "uLightColor[" + id + "]";
		const std::string light_fallout = "uFalloff[" + id + "]";
		
		const LightName lightNameStruct =
		{
			pos.c_str(), 
			light_color.c_str(), 
			light_fallout.c_str()
		};
		
		lightIDToName.insert(lightIDToName.end(), lightNameStruct);
	}

	spriteRenderer->shader.SetVector3f(lightIDToName[i].pos, glm::vec3(lightPos, 0.1f));
	spriteRenderer->shader.SetVector4f(lightIDToName[i].color, lightColor);
	spriteRenderer->shader.SetVector3f(lightIDToName[i].falloff, falloff);
	i += 1;
}

void Renderer::renderSprite(SpriteRenderer* spriteRenderer, const glm::vec2 position, const glm::vec2 size, const float rotation) const
{
	if (position.x + size.x < 0 || position.x > windowSize.x || position.y + size.y < 0 || position.y > windowSize.y)
	{
		return;
	}
	
	spriteRenderer->shader.Use();
	auto model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(position, 0.0f));  

	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); 
	model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f)); 
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

	model = glm::scale(model, glm::vec3(size, 1.0f)); 
  
	spriteRenderer->shader.SetMatrix4("model", model);

	int i = 0;
	if (showMouseLight)
	{
		DoLight(spriteRenderer, i, Input::getMousePosition(), {1.0f, 0.75f, 0.3f, 1.0f}, {0.4f, 3.0f, 20.0f});	
	}
	
	for (const Light* light : lightRenderQueue)
	{
		auto lightPosition = light->owner->getTransform()->GetPosition();
		DoLight(spriteRenderer, i, lightPosition, light->getColor(), light->getFalloff());	
	}
	
	spriteRenderer->shader.SetInteger("uLightCount", glm::clamp(i, 0, 10));

	glActiveTexture(GL_TEXTURE1);
	spriteRenderer->normals.Bind();
	
	glActiveTexture(GL_TEXTURE0);
	spriteRenderer->texture.Bind();

	glBindVertexArray(spriteRenderer->quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void Renderer::init()
{
	Griddy::Events::subscribe(this, &Renderer::addToRenderQueue);
	Griddy::Events::subscribe(this, &Renderer::removeFromRenderQueue);
	Griddy::Events::subscribe(this, &Renderer::addToLightQueue);
	Griddy::Events::subscribe(this, &Renderer::removeFromLightQueue);
	Griddy::Events::subscribe(this, &Renderer::onDebugEvent);
}

void Renderer::addToRenderQueue(const OnSpriteRendererComponentStarted* event)
{
	event->spriteRenderer->shader.SetVector3f("spriteColor", event->spriteRenderer->getColor());
	spriteRenderQueue.push_back(event->spriteRenderer);
}

void Renderer::removeFromRenderQueue(const OnSpriteRendererComponentRemoved* event)
{
	spriteRenderQueue.erase(std::ranges::remove(spriteRenderQueue, event->spriteRenderer).begin(), spriteRenderQueue.end());
}

void Renderer::addToLightQueue(const OnLightComponentStarted* event)
{
	lightRenderQueue.push_back(event->light);
}

void Renderer::removeFromLightQueue(const OnLightComponentRemoved* event)
{
	lightRenderQueue.erase(std::ranges::remove(lightRenderQueue, event->light).begin(), lightRenderQueue.end());
}

void Renderer::onDebugEvent(const OnDebugEventChanged* event)
{
	if (event->key == DebugMouseLight)
		showMouseLight = !showMouseLight;

	if (event->key == DebugLightColor)
		debugLightColor = !debugLightColor;
		
}


#include "SpriteComponent.h"

#include "Core/Renderer/ResourceManager.h"
#include "Util/Events/Events.h"
#include "Util/Events/RenderEvents.h"

void SpriteComponent::destroy()
{
	Component::destroy();
	Griddy::Events::invoke<OnSpriteRendererComponentRemoved>(this);
}

void SpriteComponent::start()
{
	Component::start();
	createBuffers();

	setColor({1, 1, 1});
	
	Griddy::Events::invoke<OnSpriteRendererComponentStarted>(this);
}

void SpriteComponent::createBuffers()
{
	if (shader.ID == 0)
		shader = ResourceManager::GetShader("sprite");
}

void SpriteComponent::update()
{
	Component::update();

	if (debugColor[0] != color.r || debugColor[1] != color.g || debugColor[2] != color.b)
		setColor({ debugColor[0], debugColor[1], debugColor[2]});
}

void SpriteComponent::lateUpdate()
{
	Component::lateUpdate();
}

void SpriteComponent::getDebugInfo(std::string* string)
{
	ImGui::Indent();
	ImGui::ColorEdit3("Color: ", debugColor);

	ImGui::TextUnformatted("TextureID: ");
	auto id = new int(texture.ID);
	ImGui::InputInt("", id);
	ImGui::Image((void *)(intptr_t)texture.ID, ImVec2(static_cast<float>(std::clamp(texture.Width, 50, 500)), static_cast<float>(std::clamp(texture.Height, 50, 250))));

	ImGui::TextUnformatted("ShaderID: ");
	id = new int(shader.ID);
	ImGui::InputInt("", id);
	ImGui::Unindent();
	
	Component::getDebugInfo(string);
}

void SpriteComponent::setColor(const glm::vec3 color)
{
	this->color = color;
	debugColor[0] = color.r;
	debugColor[1] = color.g;
	debugColor[2] = color.b;
	shader.SetVector3f("spriteColor", color, true);
}

Shader SpriteComponent::getShader() const
{
	return shader;
}

void SpriteComponent::setShader(const Shader shader)
{
	this->shader = shader;
}

void SpriteComponent::setLit(const bool lit)
{
	setShader(ResourceManager::GetShader(lit ? "sprite" : "spriteunlit"));
}

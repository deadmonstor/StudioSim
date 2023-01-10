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
}

void SpriteComponent::lateUpdate()
{
	Component::lateUpdate();
}

void SpriteComponent::getDebugInfo(std::string* string)
{
	ImGui::Indent();
	ImGui::TextUnformatted("Color: ");
	const auto internalColor = new float[3]{ this->color.r, this->color.g, this->color.b};
	ImGui::ColorEdit3("", internalColor);

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

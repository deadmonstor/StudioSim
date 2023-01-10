#include "Transform.h"

#include <sstream>

#include "Core/GameObject.h"
#include "Core/Renderer/Renderer.h"

void Transform::getDebugInfo(std::string* string)
{
	ImGui::Indent();
	ImGui::TextUnformatted("Position: ");
	const auto internalPos = new float[2]{ this->position.x, this->position.y};
	ImGui::DragFloat2("", internalPos);

	ImGui::TextUnformatted("Rotation: ");
	auto id = new int(rotation);
	ImGui::InputInt("", id);

	ImGui::TextUnformatted("Size: ");
	const auto internalSize = new float[2]{ this->size.x, this->size.y};
	ImGui::DragFloat2("", internalSize);
	ImGui::Unindent();

	Component::getDebugInfo(string);
}

glm::vec2 Transform::GetPosition() const
{
	const glm::vec2 camPos = Renderer::Instance()->getCameraPos();
	return position - camPos;
}

void Transform::SetPosition(const glm::vec2 inPosition)
{
	const glm::vec2 camPos = Renderer::Instance()->getCameraPos();
	this->position = inPosition + camPos;
}

void Transform::SetRotation(const float inRotation)
{
	this->rotation = inRotation;
}

void Transform::SetScale(const glm::vec2 inScale)
{
	this->size = inScale;
}

#include "Camera.h"

#include "Transform.h"
#include "Core/Renderer/Renderer.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

void Camera::screenSizeChanged()
{
    const glm::vec2 value = Renderer::getWindowSize();

    const float aspect = value.x / value.y;
    const float size = getSize();
    projectionMatrix = glm::ortho(-aspect * size, aspect * size, -size, size, -1.0f, 1.0f);
    viewProjectionMatrix = projectionMatrix * viewMatrix;
}

void Camera::start()
{
    Component::start();

    screenSizeChanged();
}

void Camera::update()
{
    Component::update();
    
    const Transform* transform = getOwner()->getTransform();
    const glm::vec2 position = transform->getPosition();

    const glm::mat4 transform_mat4 =
                translate(glm::mat4(1.0), glm::vec3(position.x, position.y, 0.0)) *
                rotate(glm::mat4(1.0), glm::radians(transform->GetRotation()), glm::vec3(0,0, 1));

    viewMatrix = inverse(transform_mat4);
    viewProjectionMatrix = projectionMatrix * viewMatrix;
}

void Camera::destroy()
{
    if (const auto renderer = Renderer::Instance(); renderer->getCamera() == this)
        renderer->setCamera(nullptr);
        
    Component::destroy();
}

void Camera::getDebugInfo(std::string* string)
{
    ImGui::Indent();
    ImGui::InputInt("Size", &debugSize);

    if (debugSize != getSize())
    {
        setSize(debugSize);
        screenSizeChanged();
    }

    ImGui::Unindent();

    Component::getDebugInfo(string);
}

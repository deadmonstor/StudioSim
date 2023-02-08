#include "Camera.h"

#include "Transform.h"
#include "Core/Renderer/Renderer.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

void Camera::screenSizeChanged()
{
    const glm::vec2 value = Renderer::getWindowSize();

    aspectRatio = value.x / value.y;
    const float size = getSize();
    projectionMatrix = glm::ortho(-aspectRatio * size, aspectRatio * size, -size, size, -1.0f, 1.0f);
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
                rotate(glm::mat4(1.0), glm::radians(transform->getRotation()), glm::vec3(0,0, 1));

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

bool Camera::isInFrustum(const glm::vec2 pos, const glm::vec2 size)
{
    const glm::vec2 halfSize = size / 2.0f;
    const glm::vec2 min = pos;
    const glm::vec2 max = pos + halfSize;

    const glm::vec4 corners[4] =
    {
        glm::vec4(min.x, min.y, 0.0f, 1.0f),
        glm::vec4(max.x, min.y, 0.0f, 1.0f),
        glm::vec4(min.x, max.y, 0.0f, 1.0f),
        glm::vec4(max.x, max.y, 0.0f, 1.0f)
    };
    
    bool isAllCornersNotIn = true;
    for (const glm::vec4& corner : corners)
    {
        const glm::vec4 transformed = viewProjectionMatrix * corner;

        if (transformed.x < -transformed.w || transformed.x > transformed.w ||
            transformed.y < -transformed.w || transformed.y > transformed.w)
        {
            // not in
        }
        else
        {
            isAllCornersNotIn = false;
            break;
        }
    }

    return !isAllCornersNotIn;
}

#include "Camera.h"

#include "Core/Renderer/Renderer.h"

void Camera::destroy()
{
    if (const auto renderer = Renderer::Instance(); renderer->getCamera() == this)
        renderer->setCamera(nullptr);
        
    Component::destroy();
}

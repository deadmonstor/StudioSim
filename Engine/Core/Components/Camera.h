#pragma once
#include "Core/Component.h"
#include "glm/matrix.hpp"

class Camera final : public Component
{
public:
    void screenSizeChanged();
    void setSize(const unsigned int _size) { this->size = _size; }
    [[nodiscard]] unsigned int getSize() const { return size; }
    [[nodiscard]] glm::mat4 getViewProjectMatrix() const { return viewProjectionMatrix; }
    [[nodiscard]] glm::mat4 getProjectMatrix() const { return projectionMatrix; }
    
    void start() override;
    void update() override;
    void destroy() override;
private:
    glm::mat4 viewProjectionMatrix = {};
    glm::mat4 projectionMatrix = {};
    glm::mat4 viewMatrix = {};
    unsigned int size = 600;
};

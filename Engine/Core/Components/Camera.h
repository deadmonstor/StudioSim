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
    [[nodiscard]] float getAspectRatio() const { return aspectRatio; }
    
    void start() override;
    void update() override;
    void destroy() override;
    void getDebugInfo(std::string*) override;
    bool isInFrustum(glm::vec2 pos, glm::vec2 size);
private:
    glm::mat4 viewProjectionMatrix = glm::mat4(1.0f);
    glm::mat4 projectionMatrix = glm::mat4(1.0f);
    glm::mat4 viewMatrix = glm::mat4(1.0f);
    unsigned int size = 300;
	float aspectRatio = 1;
    int debugSize = 300;
};

#include "VictoryScene.h"

#include "Core/AudioEngine.h"
#include "Core/SceneManager.h"
#include "Core/Components/Camera.h"
#include "Core/Components/TextRenderer.h"
#include "Core/Renderer/Renderer.h"
#include "Util/Events/Events.h"

void VictoryScene::init()
{
    AudioEngine::Instance()->stopChannelGroup("Master Channel");
    
    engineRenderID = Griddy::Events::subscribe(this, &VictoryScene::onEngineRender);
    keyDownID = Griddy::Events::subscribe(this, &VictoryScene::onKeyDown);

    GameObject* cam = SceneManager::Instance()->createGameObject("camera", glm::vec2{0, 0});
    cam->addComponent<Camera>();
    Renderer::Instance()->setCamera(cam->getComponent<Camera>());
}

void VictoryScene::destroy()
{
    Griddy::Events::unsubscribe(this, &VictoryScene::onEngineRender, engineRenderID);
    Griddy::Events::unsubscribe(this, &VictoryScene::onKeyDown, keyDownID);
}

void VictoryScene::onEngineRender(const OnEngineRender* event)
{
    if (SceneManager::Instance()->isLoadingScene() ||
        SceneManager::Instance()->isShuttingDown() ||
        SceneManager::Instance()->getScene()->name != "victoryScreen") return;
    
    const auto MiddleTopHalf =
                    glm::vec2((Renderer::getWindowSize().x / 2), (Renderer::getWindowSize().y / 1.5)) / Renderer::Instance()->getAspectRatio();

    const auto MiddleMiddle =
                  glm::vec2((Renderer::getWindowSize().x / 2), (Renderer::getWindowSize().y / 2.5)) / Renderer::Instance()->getAspectRatio();
    
    glm::vec2 sizeOfText = TextRenderer::Instance()->renderTextSize("Victory!", 1);
    TextRenderer::Instance()->renderText(" Victory!", MiddleTopHalf.x - (sizeOfText.x / 2),
        MiddleTopHalf.y - (sizeOfText.y / 2), 1, glm::vec3{1, 1, 1}, glm::vec2{0, 0});

    sizeOfText = TextRenderer::Instance()->renderTextSize( "Press Enter to Submit Score", 1);
    TextRenderer::Instance()->renderText(" Press Enter to Submit Score", MiddleMiddle.x - (sizeOfText.x / 2),
        MiddleMiddle.y - (sizeOfText.y / 2), 1, glm::vec3{1, 1, 1}, glm::vec2{0, 0});
}

void VictoryScene::onKeyDown(const OnKeyDown* event)
{
    if (event->key == GLFW_KEY_ENTER)
    {
        SceneManager::Instance()->changeScene("scoreScene");
    }
}

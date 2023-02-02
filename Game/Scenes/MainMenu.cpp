#include "MainMenu.h"

#include "Core/SceneManager.h"
#include "Core/Components/Camera.h"
#include "Core/Components/TextRenderer.h"
#include "Core/Renderer/Renderer.h"
#include "Util/Events/Events.h"

void MainMenu::init()
{
    Griddy::Events::subscribe(this, &MainMenu::onSceneChanged);
    Griddy::Events::subscribe(this, &MainMenu::onEngineRender);
    Griddy::Events::subscribe(this, &MainMenu::onKeyDown);
}

void MainMenu::onSceneChanged(const OnSceneChanged* event)
{
    if (event->key == "mainMenu")
    {
        // create game object for camera
        GameObject* cam = SceneManager::Instance()->createGameObject("test", glm::vec2{0, 0});
        cam->addComponent<Camera>();
        Renderer::Instance()->setCamera(cam->getComponent<Camera>());
    }
}

void MainMenu::onEngineRender(const OnEngineRender* event)
{
    if (SceneManager::Instance()->isLoadingScene() ||
        SceneManager::Instance()->isShuttingDown() ||
        SceneManager::Instance()->getScene()->name != "mainMenu") return;
    

    const auto MiddleTopHalf =
                    glm::vec2((Renderer::getWindowSize().x / 2), (Renderer::getWindowSize().y / 1.5)) / Renderer::Instance()->getAspectRatio();

    const auto MiddleMiddle =
                  glm::vec2((Renderer::getWindowSize().x / 2), (Renderer::getWindowSize().y / 2.5)) / Renderer::Instance()->getAspectRatio();
    
    glm::vec2 sizeOfText = TextRenderer::Instance()->renderTextSize("Into the Crypt", 1);
    TextRenderer::Instance()->renderText(" Into the Crypt", MiddleTopHalf.x - (sizeOfText.x / 2),
        MiddleTopHalf.y - (sizeOfText.y / 2), 1, glm::vec3{1, 1, 1}, glm::vec2{0, 0});

    sizeOfText = TextRenderer::Instance()->renderTextSize( "Press Enter to Start", 1);
    TextRenderer::Instance()->renderText(" Press Enter to Start", MiddleMiddle.x - (sizeOfText.x / 2),
        MiddleMiddle.y - (sizeOfText.y / 2), 1, glm::vec3{1, 1, 1}, glm::vec2{0, 0});
}

void MainMenu::onKeyDown(const OnKeyDown* event)
{
    if (event->key == GLFW_KEY_ENTER)
    {
        SceneManager::Instance()->changeScene("level1");
    }
}

#include "MainMenu.h"

#include "Core/SceneManager.h"
#include "Core/Components/Camera.h"
#include "Core/Components/TextRenderer.h"
#include "Core/Renderer/Renderer.h"
#include "Util/Time.h"
#include "Util/Events/Events.h"

void MainMenu::init()
{
    engineRenderID = Griddy::Events::subscribe(this, &MainMenu::onEngineRender);
    keyDownID = Griddy::Events::subscribe(this, &MainMenu::onKeyDown);

    GameObject* cam = SceneManager::Instance()->createGameObject("camera", glm::vec2{0, 0});
    cam->addComponent<Camera>();
    Renderer::Instance()->setCamera(cam->getComponent<Camera>());
}

void MainMenu::destroy()
{
    Griddy::Events::unsubscribe(this, &MainMenu::onEngineRender, engineRenderID);
    Griddy::Events::unsubscribe(this, &MainMenu::onKeyDown, keyDownID);
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
    TextRenderer::Instance()->renderText(" Into the Crypt", MiddleTopHalf.x - (sizeOfText.x),
        MiddleTopHalf.y - (sizeOfText.y), 2, glm::vec3{1, 1, 1}, glm::vec2{0, 0});

    const auto base_value = Time::getTime();

    const auto r = 0.5 * (sin(base_value - 2)	    + 1);
    const auto g = 0.5 * (sin(base_value + 2)	    + 1);
    const auto b = 0.5 * (sin(base_value      )	    + 1);
    
    sizeOfText = TextRenderer::Instance()->renderTextSize( "Press Enter to Start", 1);
    TextRenderer::Instance()->renderText(" Press Enter to Start", MiddleMiddle.x - (sizeOfText.x / 2),
        MiddleMiddle.y - (sizeOfText.y / 2), 1, glm::vec3(r,g,b), glm::vec2{0, 0});
}

void MainMenu::onKeyDown(const OnKeyDown* event)
{
    if (event->key == GLFW_KEY_ENTER)
    {
        SceneManager::Instance()->changeScene("tutorial");
    }
}

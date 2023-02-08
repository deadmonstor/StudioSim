#include "MainMenu.h"

#include "UIManager.h"
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

    if (!ResourceManager::HasTexture("backgroundMainMenu"))
        ResourceManager::LoadTexture("Sprites/background.png", "backgroundMainMenu");
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
                    glm::vec2((Renderer::getViewportSize().x / 2), (Renderer::getViewportSize().y / 1.35));

    const auto MiddleMiddle =
                  glm::vec2((Renderer::getViewportSize().x / 2), (Renderer::getViewportSize().y / 2));
    
    const auto MiddleBottom =
                  glm::vec2((Renderer::getViewportSize().x / 2), (Renderer::getViewportSize().y / 3.25));

    static SpriteComponent* sprite = new SpriteComponent();
    sprite->setLit(false);
    sprite->setTexture(ResourceManager::GetTexture("backgroundMainMenu"));
    sprite->setPivot(Pivot::Center);
    Renderer::Instance()->renderSprite(sprite, Renderer::Instance()->getCameraPos(), {801 / 2, 676 / 2}, 0);
    
    glm::vec2 sizeOfText = TextRenderer::Instance()->renderTextSize("Into the Crypt", 2.03f);
    TextRenderer::Instance()->renderText(" Into the Crypt", MiddleTopHalf.x - (sizeOfText.x / 2),
        MiddleTopHalf.y - (sizeOfText.y / 2), 2.03f, glm::vec3{0.8f, 0.2f, 0.2f}, glm::vec2{0, 0});
    
    sizeOfText = TextRenderer::Instance()->renderTextSize("Into the Crypt", 2);
    TextRenderer::Instance()->renderText(" Into the Crypt", MiddleTopHalf.x - (sizeOfText.x / 2),
        MiddleTopHalf.y - (sizeOfText.y / 2), 2, glm::vec3{1, 1, 1}, glm::vec2{0, 0});


    const auto base_value = Time::getTime();

    const auto r = 0.5 * (sin(base_value - 2)	    + 1);
    const auto g = 0.5 * (sin(base_value + 2)	    + 1);
    const auto b = 0.5 * (sin(base_value      )	    + 1);

    sizeOfText = TextRenderer::Instance()->renderTextSize( "Press Enter to Start", 1.01f);
    TextRenderer::Instance()->renderText(" Press Enter to Start", MiddleBottom.x - (sizeOfText.x / 2),
        MiddleBottom.y - (sizeOfText.y / 2), 1.01f, glm::vec3(r,g,b), glm::vec2{0, 0});
    
    sizeOfText = TextRenderer::Instance()->renderTextSize( "Press Enter to Start", 1);
    TextRenderer::Instance()->renderText(" Press Enter to Start", MiddleBottom.x - (sizeOfText.x / 2),
        MiddleBottom.y - (sizeOfText.y / 2), 1, glm::vec3(1, 1, 1), glm::vec2{0, 0});
}

void MainMenu::onKeyDown(const OnKeyDown* event)
{
    if (event->key == GLFW_KEY_ENTER)
    {
        SceneManager::Instance()->changeScene("tutorial");
    }
}

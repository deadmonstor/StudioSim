#include "ScoreScene.h"
#include "../ScoreSystem.h"
#include "Core/SceneManager.h"
#include "Core/Components/Camera.h"
#include "Core/Components/TextRenderer.h"
#include "Core/Renderer/Renderer.h"
#include "Util/Events/Events.h"

void ScoreScene::init()
{
    engineRenderID = Griddy::Events::subscribe(this, &ScoreScene::onEngineRender);
    charKeyDownID = Griddy::Events::subscribe(this, &ScoreScene::OnCharacterKeyDown);
    keyDownID = Griddy::Events::subscribe(this, &ScoreScene::OnActualDown);

    GameObject* cam = SceneManager::Instance()->createGameObject("test", glm::vec2{ 0, 0 });
    cam->addComponent<Camera>();
    Renderer::Instance()->setCamera(cam->getComponent<Camera>());
}

void ScoreScene::update()
{
}

void ScoreScene::destroy()
{
    Griddy::Events::unsubscribe(this, &ScoreScene::onEngineRender, engineRenderID);
    Griddy::Events::unsubscribe(this, &ScoreScene::OnCharacterKeyDown, charKeyDownID);
    Griddy::Events::unsubscribe(this, &ScoreScene::OnActualDown, keyDownID);
}

void ScoreScene::onEngineRender(const OnEngineRender* event)
{
    if (SceneManager::Instance()->isLoadingScene() ||
        SceneManager::Instance()->isShuttingDown() ||
        SceneManager::Instance()->getScene()->name != "scoreScene") return;

    const auto MiddleTopHalf =
        glm::vec2((Renderer::getWindowSize().x / 2), (Renderer::getWindowSize().y / 1.5)) / Renderer::Instance()->getAspectRatio();

    const auto MiddleMiddle =
        glm::vec2((Renderer::getWindowSize().x / 2), (Renderer::getWindowSize().y / 2.5)) / Renderer::Instance()->getAspectRatio();

    glm::vec2 sizeOfText = TextRenderer::Instance()->renderTextSize(playerName, 1);
    TextRenderer::Instance()->renderText(playerName, MiddleTopHalf.x - (sizeOfText.x / 2),
        MiddleTopHalf.y - (sizeOfText.y / 2), 1, glm::vec3{ 1, 1, 1 }, glm::vec2{ 0, 0 });

    sizeOfText = TextRenderer::Instance()->renderTextSize("Enter Your Name:", 1);
    TextRenderer::Instance()->renderText("Enter Your Name:", MiddleTopHalf.x - (sizeOfText.x / 2),
        MiddleTopHalf.y - (sizeOfText.y / 2) + 50, 1, glm::vec3{1, 1, 1}, glm::vec2{0, 0});
}

void ScoreScene::OnCharacterKeyDown(const OnCharacterDown* event)
{
    //std::cout << (char)event->key << "\n";
    if (playerName.length() < 3)
    {
        playerName += (char)event->key;
    }
}

void ScoreScene::OnActualDown(const OnKeyDown* event)
{
    if (event->key == GLFW_KEY_BACKSPACE)
    {
        if (playerName.length() > 0)
        {
            std::cout << "Erase \n";
            playerName.pop_back();
        }
    }
    else if (event->key == GLFW_KEY_ENTER && playerName.length() == 3 && !hasSaved)
    {
        ScoreSystem::Instance()->SaveScore(playerName.c_str());
        hasSaved = true;
    }
}




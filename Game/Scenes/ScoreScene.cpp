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

    const auto MiddleTop =
        glm::vec2((Renderer::getWindowSize().x / 2), (Renderer::getWindowSize().y)) / Renderer::Instance()->getAspectRatio();

    const auto MiddleTopHalf =
        glm::vec2((Renderer::getWindowSize().x / 2), (Renderer::getWindowSize().y / 1.5)) / Renderer::Instance()->getAspectRatio();

    const auto MiddleMiddle =
        glm::vec2((Renderer::getWindowSize().x / 2), (Renderer::getWindowSize().y / 2.5)) / Renderer::Instance()->getAspectRatio();

    const auto MiddleBottom =
        glm::vec2((Renderer::getWindowSize().x / 2), (Renderer::getWindowSize().y / 5)) / Renderer::Instance()->getAspectRatio();

    //Player Name
    glm::vec2 sizeOfText = TextRenderer::Instance()->renderTextSize(playerName, 1);
    TextRenderer::Instance()->renderText(playerName, MiddleBottom.x - (sizeOfText.x / 2),
        MiddleBottom.y - (sizeOfText.y / 2), 1, glm::vec3{ 1, 1, 1 }, glm::vec2{ 0, 0 });

    //Enter Name Text
    sizeOfText = TextRenderer::Instance()->renderTextSize("Enter Your Name:", 1);
    TextRenderer::Instance()->renderText("Enter Your Name:", MiddleBottom.x - (sizeOfText.x / 2),
        MiddleBottom.y - (sizeOfText.y / 2) + 50, 1, glm::vec3{1, 1, 1}, glm::vec2{0, 0});

    //Score Details
    sizeOfText = TextRenderer::Instance()->renderTextSize("Your Score Breakdown:", 1);
    TextRenderer::Instance()->renderText("Your Score Breakdown:", MiddleTop.x - (sizeOfText.x / 2),
        MiddleTop.y - (sizeOfText.y / 2) - 50, 1, glm::vec3{ 1, 1, 1 }, glm::vec2{ 0, 0 });

    //Total Score
    sizeOfText = TextRenderer::Instance()->renderTextSize("Total Score: " + std::format("{:.2f}", ScoreSystem::Instance()->getScore()), 1);
    TextRenderer::Instance()->renderText("Total Score: " + std::format("{:.0f}", ScoreSystem::Instance()->getScore()), MiddleTop.x - (sizeOfText.x / 2),
        MiddleTop.y - (sizeOfText.y / 2) - 100, 1, glm::vec3{ 1, 1, 1 }, glm::vec2{ 0, 0 });

    //Enemies Killed
    sizeOfText = TextRenderer::Instance()->renderTextSize("Enemies Killed: " + std::to_string(ScoreSystem::Instance()->getEnemiesKilled()), 1);
    TextRenderer::Instance()->renderText("Enemies Killed: " + std::to_string(ScoreSystem::Instance()->getEnemiesKilled()), MiddleTop.x - (sizeOfText.x / 2),
        MiddleTop.y - (sizeOfText.y / 2) - 150, 1, glm::vec3{ 1, 1, 1 }, glm::vec2{ 0, 0 });

    //Enemies Killed
    sizeOfText = TextRenderer::Instance()->renderTextSize("Tiles Moved: " + std::to_string(ScoreSystem::Instance()->getTilesMoved()), 1);
    TextRenderer::Instance()->renderText("Tiles Moved: " + std::to_string(ScoreSystem::Instance()->getTilesMoved()), MiddleTop.x - (sizeOfText.x / 2),
        MiddleTop.y - (sizeOfText.y / 2) - 200, 1, glm::vec3{ 1, 1, 1 }, glm::vec2{ 0, 0 });

    //Enemies Killed
    sizeOfText = TextRenderer::Instance()->renderTextSize("Damage Taken: " + std::to_string(ScoreSystem::Instance()->getDamageTaken()), 1);
    TextRenderer::Instance()->renderText("Damage Taken: " + std::to_string(ScoreSystem::Instance()->getDamageTaken()), MiddleTop.x - (sizeOfText.x / 2),
        MiddleTop.y - (sizeOfText.y / 2) - 250, 1, glm::vec3{ 1, 1, 1 }, glm::vec2{ 0, 0 });

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
        SceneManager::Instance()->changeScene("leaderboardScene");
    }
}




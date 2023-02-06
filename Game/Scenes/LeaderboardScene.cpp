#include "LeaderboardScene.h"
#include "../ScoreSystem.h"
#include "Core/SceneManager.h"
#include "Core/Components/Camera.h"
#include "Core/Components/TextRenderer.h"
#include "Core/Renderer/Renderer.h"
#include "Util/Events/Events.h"

void LeaderboardScene::init()
{
    engineRenderID = Griddy::Events::subscribe(this, &LeaderboardScene::onEngineRender);
    keyDownID = Griddy::Events::subscribe(this, &LeaderboardScene::OnActualDown);

    GameObject* cam = SceneManager::Instance()->createGameObject("camera", glm::vec2{ 0, 0 });
    cam->addComponent<Camera>();
    Renderer::Instance()->setCamera(cam->getComponent<Camera>());
    ScoreSystem::Instance()->ReadScores(false);
}

void LeaderboardScene::update()
{
}

void LeaderboardScene::destroy()
{
    Griddy::Events::unsubscribe(this, &LeaderboardScene::onEngineRender, engineRenderID);
    Griddy::Events::unsubscribe(this, &LeaderboardScene::OnActualDown, keyDownID);
}

void LeaderboardScene::onEngineRender(const OnEngineRender* event)
{
    if (SceneManager::Instance()->isLoadingScene() ||
        SceneManager::Instance()->isShuttingDown() ||
        SceneManager::Instance()->getScene()->name != "leaderboardScene") return;

    ScoreSystem::Instance()->RenderTopScores();
}

void LeaderboardScene::OnActualDown(const OnKeyDown* event)
{
    if (event->key == GLFW_KEY_ENTER)
    {
        SceneManager::Instance()->changeScene("mainMenu");
    }
}

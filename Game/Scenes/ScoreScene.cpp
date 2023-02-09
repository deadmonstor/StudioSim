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

	GameObject* cam = SceneManager::Instance()->createGameObject("camera", glm::vec2{0, 0});
	cam->addComponent<Camera>();
	Renderer::Instance()->setCamera(cam->getComponent<Camera>());
}

void ScoreScene::update() {}

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
		SceneManager::Instance()->getScene()->name != "scoreScene")
		return;

	const auto MiddleTop =
		glm::vec2((Renderer::getViewportSize().x / 2), (Renderer::getViewportSize().y));
	
	const auto MiddleBottom =
		glm::vec2((Renderer::getViewportSize().x / 2), (Renderer::getViewportSize().y / 5));

	//Player Name
	glm::vec2 sizeOfText = TextRenderer::Instance()->renderTextSize(playerName, 1);
	TextRenderer::Instance()->renderText(playerName, MiddleBottom.x - (sizeOfText.x / 2),
	                                     MiddleBottom.y - (sizeOfText.y / 2), 1, glm::vec3{1, 1, 1}, glm::vec2{0, 0});

	//Enter Name Text
	sizeOfText = TextRenderer::Instance()->renderTextSize("Enter Your Name:", 1);
	TextRenderer::Instance()->renderText("Enter Your Name:",
	                                     MiddleBottom.x - (sizeOfText.x / 2),
	                                     MiddleBottom.y - (sizeOfText.y / 2) + 50,
	                                     1,
	                                     glm::vec3{1, 1, 1},
	                                     glm::vec2{0, 0});

	//Score Details
	sizeOfText = TextRenderer::Instance()->renderTextSize("Your Score Breakdown:", 1);
	TextRenderer::Instance()->renderText("Your Score Breakdown:",
	                                     MiddleTop.x - (sizeOfText.x / 2),
	                                     MiddleTop.y - (sizeOfText.y / 2) - 50,
	                                     1,
	                                     glm::vec3{1, 1, 1},
	                                     glm::vec2{0, 0});

	ScoreSystem::Instance()->calcFinalScore();
	//Total Score
	sizeOfText = TextRenderer::Instance()->renderTextSize(
		"Total Score: " + std::format("{:.0f}", ScoreSystem::Instance()->getScore()), 1);
	TextRenderer::Instance()->renderText("Total Score: " + std::format("{:.0f}", ScoreSystem::Instance()->getScore()),
	                                     MiddleTop.x - (sizeOfText.x / 2),
	                                     MiddleTop.y - (sizeOfText.y / 2) - 335,
	                                     1,
	                                     glm::vec3{1, 1, 1},
	                                     glm::vec2{0, 0});

	//Enemies Killed
	sizeOfText = TextRenderer::Instance()->renderTextSize(
		"Enemies Killed: " + std::to_string(ScoreSystem::Instance()->getEnemiesKilled()), 0.6f);
	TextRenderer::Instance()->renderText(
		"Enemies Killed: " + std::to_string(ScoreSystem::Instance()->getEnemiesKilled()),
		MiddleTop.x - (sizeOfText.x / 2),
		MiddleTop.y - (sizeOfText.y / 2) - 125, 0.6f, glm::vec3{1, 1, 1}, glm::vec2{0, 0});

	//Tiles Moved
	sizeOfText = TextRenderer::Instance()->renderTextSize(
		"Tiles Moved: " + std::to_string(ScoreSystem::Instance()->getTilesMoved()), 0.6f);
	TextRenderer::Instance()->renderText("Tiles Moved: " + std::to_string(ScoreSystem::Instance()->getTilesMoved()),
	                                     MiddleTop.x - (sizeOfText.x / 2),
	                                     MiddleTop.y - (sizeOfText.y / 2) - 175, 0.6f, glm::vec3{1, 1, 1},
	                                     glm::vec2{0, 0});

	//Damage Taken
	sizeOfText = TextRenderer::Instance()->renderTextSize(
		"Damage Taken: " + std::to_string(ScoreSystem::Instance()->getDamageTaken()), 0.6f);
	TextRenderer::Instance()->renderText("Damage Taken: " + std::to_string(ScoreSystem::Instance()->getDamageTaken()),
	                                     MiddleTop.x - (sizeOfText.x / 2),
	                                     MiddleTop.y - (sizeOfText.y / 2) - 225, 0.6f, glm::vec3{1, 1, 1},
	                                     glm::vec2{0, 0});

	sizeOfText = TextRenderer::Instance()->renderTextSize(
	"Gold Earned: " + std::to_string(ScoreSystem::Instance()->getGoldEarned()), 0.6f);
	TextRenderer::Instance()->renderText("Gold Earned: " + std::to_string(ScoreSystem::Instance()->getGoldEarned()),
										 MiddleTop.x - (sizeOfText.x / 2),
										 MiddleTop.y - (sizeOfText.y / 2) - 275, 0.6f, glm::vec3{1, 1, 1},
										 glm::vec2{0, 0});
}

void ScoreScene::OnCharacterKeyDown(const OnCharacterDown* event)
{
	char character = static_cast<char>(event->key);
	if (playerName.length() < 3) 
	{ 
		playerName += std::toupper(character);
	}
}

void ScoreScene::OnActualDown(const OnKeyDown* event)
{
	if (event->key == GLFW_KEY_BACKSPACE) { if (playerName.length() > 0) { playerName.pop_back(); } }
	else if (event->key == GLFW_KEY_ENTER && playerName.length() == 3 && !hasSaved)
	{
		ScoreSystem::Instance()->SaveScore(playerName);
		hasSaved = true;
		SceneManager::Instance()->changeScene("leaderboardScene");
	}
}

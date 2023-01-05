#include "MainGame.h"
#include <Util/Logger.h>
#include "TestClass.h"
#include "WindowManager.h"
#include "Util/Events/Events.h"

int main(int, char**)
{
	if (!MainGame::Instance()->init())
	{
		LOG_ERROR("Failed to initialize the game");
		return -1;
	}

	const auto WindowManager = WindowManager::Instance();
	WindowManager->SetWindowTitle("Game Name Here");
	WindowManager->SetWindowSize({ 1920, 1080 });

	const auto Events = Disunity::Events::Instance();
	Events->subscribe(TestClass::Instance(), &TestClass::TestFunc);
	Events->invoke(new Disunity::Event());

	MainGame::Instance()->run();
	return 0;
}
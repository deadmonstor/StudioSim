#include "MainGame.h"
#include <Util/Logger.h>
#include "TestClass.h"
#include "WindowManager.h"
#include "Util/Events/Events.h"

int main(int, char **)
{
	if (!MainGame::Instance()->init())
	{
		LOG_ERROR("Failed to initialize the game");
		return -1;
	}
	
	WindowManager::Instance()->SetWindowTitle("Game Name Here");
	Disunity::Events::Instance()->subscribe(TestClass::Instance(), &TestClass::TestFunc);
	Disunity::Events::Instance()->invoke(new Disunity::Event());

	MainGame::Instance()->run();
	return 0;
}
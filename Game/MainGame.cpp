#include "MainGame.h"
#include <Util/Logger.h>

int main(int, char**)
{
	MainGame::GetInstance()->run();
	return 0;
}
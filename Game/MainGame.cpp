#include "MainGame.h"
#include <Util/Logger.h>

int main(int, char**)
{
	MainGame::Instance()->run();
	return 0;
}
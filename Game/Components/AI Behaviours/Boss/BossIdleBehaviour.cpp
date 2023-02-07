#include "BossIdleBehaviour.h"

FunctionMap BossIdleBehaviour::CreateFunctionMap()
{
	FunctionMap map = {};
	//map[typeid(OnKeyDown)] =
	//	[](Behaviour* pointer, Griddy::Event* event)
	//{
	//	dynamic_cast<BossIdleBehaviour*>(pointer)->onPlayerEnterBossRoom(event);
	//};
	return map;
}

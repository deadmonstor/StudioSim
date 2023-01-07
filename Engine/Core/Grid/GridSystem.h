#pragma once
#include <map>

#include "Tile.h"
#include "Util/SingletonTemplate.h"
#include "Util/Events/EngineEvents.h"

class Texture;
struct GridHolder
{
	Tile* tile;
};

class GridSystem : public SingletonTemplate<GridSystem>
{
	std::map<int, std::map<int, GridHolder*>> map;
	bool shouldRender = true;
	
public:
	GridSystem();
	void render();
	void onDebugEvent(const OnDebugEventChanged*);
};
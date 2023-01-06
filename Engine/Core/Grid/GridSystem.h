#pragma once
#include <map>

#include "Tile.h"
#include "Util/SingletonTemplate.h"

class Texture;
struct GridHolder
{
	Tile* tile;
};

class GridSystem : public SingletonTemplate<GridSystem>
{
	std::map<int, std::map<int, GridHolder*>> map;
	
public:
	GridSystem();
	void render();
};
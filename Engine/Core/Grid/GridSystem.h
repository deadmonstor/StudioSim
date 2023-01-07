﻿#pragma once
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
	std::map<int, std::map<int, GridHolder*>> internalMap;
	bool shouldRender = false;
	
public:
	glm::fvec2 tileSize { 0,0 };
	glm::ivec2 gridSize { 0,0 };
	void init(glm::fvec2 _tileSize, glm::ivec2 _gridSize);

	Tile* getTile(const glm::ivec2& _pos);
	
	void render();
	void onDebugEvent(const OnDebugEventChanged*);
};
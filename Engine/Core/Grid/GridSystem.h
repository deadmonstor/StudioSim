#pragma once
#include <map>

#include "Tile.h"
#include "Util/SingletonTemplate.h"
#include "Util/Events/EngineEvents.h"

class Texture;
struct GridHolder
{
	Tile* tile;
	bool isOccupied;
	bool isWall;
};

struct GridLayer
{
	std::map<int, std::map<int, GridHolder*>> internalMap = {};
	std::map<int, Texture> textureMap = {};
	
	std::vector<int> wallIDs = {};
	std::vector<int> emptyTiles = {};
};

class GridSystem : public SingletonTemplate<GridSystem>
{
	std::map<int, GridLayer*> gridLayers;
	std::map<int, SortingLayer&> orderSortingMap;
	bool shouldRender = true;
	friend class ImGuiHandler;
	
public:
	glm::fvec2 tileSize { 0,0 };
	glm::ivec2 gridSize { 0,0 };

	void clearGrid(int id);
	void renderInternal(int id);
	void loadFromFile(int id, const std::string& fileName);
	
	void setTextureMap(int id, const std::map<int, Texture>& textureMap);
	void setWallIDs(int id, const std::vector<int>& wallIDs);
	void setEmptyTileIDs(int id, const std::vector<int>& emptyTileIDs);

	void setOrderMap(const std::map<int, SortingLayer&>& _sortingMap) { this->orderSortingMap = _sortingMap; }
	std::map<int, SortingLayer&>& getOrderMap() { return this->orderSortingMap; }

	Tile* getTile(int id, const glm::ivec2& _pos);
	void init(glm::fvec2 _tileSize, glm::ivec2 _gridSize);
	void render();
	void onDebugEvent(const OnDebugEventChanged*);
};
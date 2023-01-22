#pragma once
#include <map>

#include "Tile.h"
#include "Core/Renderer/Lighting.h"
#include "Util/SingletonTemplate.h"
#include "Util/Events/EngineEvents.h"

class Texture;
struct TileHolder
{
	Tile* tile;
	GameObject* gameObjectSatOnTile;

	bool isSpawned;
	bool isWall;
};

struct GridLayer
{
	std::map<int, std::map<int, TileHolder*>> internalMap = {};
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
	
	glm::fvec2 tileSize { 0,0 };
	glm::ivec2 gridSize { 0,0 };
public:

	void render();
	void renderInternal(int id);
	
	void setTextureMap(int id, const std::map<int, Texture>& textureMap);
	void setWallIDs(int id, const std::vector<int>& wallIDs);
	void setEmptyTileIDs(int id, const std::vector<int>& emptyTileIDs);
	void setOrderMap(const std::map<int, SortingLayer&>& _sortingMap) { this->orderSortingMap = _sortingMap; }

	std::map<int, SortingLayer&>& getOrderMap() { return this->orderSortingMap; }
	glm::ivec2 getGridSize() { return gridSize; }
	glm::fvec2 getTileSize() { return tileSize; }
	TileHolder* getTileHolder(int id, const glm::ivec2& _pos);
	GridLayer* GetGridLayer(int id);

	void init(glm::fvec2 _tileSize, glm::ivec2 _gridSize);
	void clearGrid(int id);
	void loadFromFile(int id, const std::string& fileName);
	void onDebugEvent(const OnDebugEventChanged*);
	void refreshLightData(LightUpdateRequest lightUpdateRequest);
	
	Tile* getTile(int id, const glm::ivec2& _pos);
	std::vector<std::pair<glm::vec2, Tile*>> getNeighbours(int id, glm::vec2 pos);
	glm::vec2 getTilePosition(glm::vec2 vec) const;
	glm::vec2 getWorldPosition(glm::vec2 vec) const;
	void setSatOnTile(int id, glm::vec2 vec, GameObject* enemy);
	void resetSatOnTile(int id, glm::vec2 vec);

};
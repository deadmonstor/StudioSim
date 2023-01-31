#pragma once
#include <map>

#include "Tiles/Tile.h"
#include "Core/Renderer/Lighting.h"
#include "Util/SingletonTemplate.h"
#include "Util/Events/EngineEvents.h"

class Texture;
struct TileHolder
{
	glm::vec2 position;
	Tile* tile;
	GameObject* gameObjectSatOnTile;

	bool isSpawned;
	bool isWall;
};

struct GridLayer
{
	std::map<int, std::map<int, TileHolder*>> internalMap = {};
	std::map<int, Texture> textureMap = {};
	std::map<int, std::function<void(glm::vec2)>> spawnFunctions = {};
	std::map<int, std::function<Tile*()>> tileFunctions = {};
	
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
	
	void renderInternal(int id);

public:
	void render();
	
	void setTextureMap(int id, const std::map<int, Texture>& textureMap);
	void setWallIDs(int id, const std::vector<int>& wallIDs);
	void setEmptyTileIDs(int id, const std::vector<int>& emptyTileIDs);
	void setOrderMap(const std::map<int, SortingLayer&>& _sortingMap) { this->orderSortingMap = _sortingMap; }
	void setSpawnFunctionMap(const int id, const std::map<int, std::function<void(glm::vec2)>>& _spawnFunction) { this->gridLayers[id]->spawnFunctions = _spawnFunction; }
	void setTileFunctionMap(const int id, const std::map<int, std::function<Tile*()>>& _tileFunctions) { this->gridLayers[id]->tileFunctions = _tileFunctions; }

	bool isWallTile(const glm::vec2 pos);
	bool isInMap(int id, const glm::vec2 pos) const;
	void setSatOnTile(int id, glm::vec2 vec, GameObject* enemy);
	void resetSatOnTile(int id, glm::vec2 vec);
	void init(glm::fvec2 _tileSize, glm::ivec2 _gridSize);
	void createTile(int id, Tile* tile);
	void clearGrid(int id);
	void loadFromFile(int id, const std::string& fileName);
	void onDebugEvent(const OnDebugEventChanged*);
	void refreshLightData(LightUpdateRequest lightUpdateRequest);
	
	Tile* getTile(int id, const glm::ivec2& _pos);
	std::map<int, SortingLayer&>& getOrderMap() { return this->orderSortingMap; }
	glm::ivec2 getGridSize() const { return gridSize; }
	glm::fvec2 getTileSize() const { return tileSize; }
	TileHolder* getTileHolder(int id, const glm::ivec2& _pos);
	GridLayer* getGridLayer(int id);
	std::vector<std::pair<glm::vec2, Tile*>> getNeighbours(int id, glm::vec2 pos);
	std::vector<TileHolder*> getPathfindingNeighbours(int id, TileHolder* tile);
	glm::vec2 getTilePosition(glm::vec2 vec) const;
	glm::vec2 getWorldPosition(glm::vec2 vec) const;

};
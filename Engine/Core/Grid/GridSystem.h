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
};

class GridSystem : public SingletonTemplate<GridSystem>
{
	friend class ImGuiHandler;
	
	std::map<int, std::map<int, GridHolder*>> internalMap;
	std::map<int, Texture> textureMap;
	bool shouldRender = true;
	
public:
	glm::fvec2 tileSize { 0,0 };
	glm::ivec2 gridSize { 0,0 };

	void init(glm::fvec2 _tileSize, glm::ivec2 _gridSize);
	Tile* getTile(const glm::ivec2& _pos);
	void loadFromFile(const std::string& fileName);
	void setTextureMap(const std::map<int, Texture>& textureMap) { this->textureMap = textureMap; }

	void render();
	void onDebugEvent(const OnDebugEventChanged*);
};
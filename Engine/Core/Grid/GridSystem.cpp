#include <glad/glad.h>
#include "GridSystem.h"
#include <regex>

#include "Core/Renderer/Lighting.h"
#include "Core/Renderer/Renderer.h"
#include "Core/Renderer/ResourceManager.h"
#include "Util/Logger.h"
#include "Util/Events/Events.h"

void GridSystem::clearGrid(const int id)
{
	if (gridLayers[id])
	{
		//TODO this is probably a mem leak, fix it later
		gridLayers[id]->internalMap.clear();
	}
	else
	{
		gridLayers[id] = new GridLayer();
	}
	
	for(int x = 0; x < gridSize.x; x++)
	{
		for(int y = 0; y < gridSize.y; y++)
		{
			TileHolder* tile_holder = gridLayers[id]->internalMap[x][y] = new TileHolder();
			tile_holder->position = glm::vec2(x, y);
			tile_holder->isOccupied = false;

			const auto tile = new Tile(Texture());
			tile->createBuffers();
			tile->setSortingLayer(orderSortingMap.at(id));
			tile->setLit(true);
			tile->setPivot(Pivot::Center);

			gridLayers[id]->internalMap[x][y]->tile = tile;
		}
	}
}

void GridSystem::init(const glm::fvec2 _tileSize, const glm::ivec2 _gridSize)
{
	tileSize = _tileSize;
	gridSize = _gridSize;

	// subscribe to the event
	Griddy::Events::subscribe(this, &GridSystem::onDebugEvent);
}

void GridSystem::renderInternal(const int id)
{
	if (!gridLayers.contains(id)) return;
	
	auto internalMap = gridLayers[id]->internalMap;
	if (internalMap.empty()) return;
	
	for(auto [x, pointer] : internalMap)
	{
		const float tileWidth = tileSize.x;
		const float tileHeight = tileSize.y;
		
		const float tileX = x * tileWidth;
		
		for(auto [y, holder] : pointer)
		{
			const float tileY = y * tileHeight;
			const auto pos = glm::vec2{tileX, tileY};

			if (!holder->isOccupied) continue;
			if (holder->tile->getTexture().Height == 0 && holder->tile->getTexture().Width == 0)
				continue;
			
			holder->tile->update();
			
			Renderer::Instance()->renderSprite(holder->tile,
			                                   pos,
			                                   {tileWidth, tileHeight},
			                                   0
			);
		}
	}
}

void GridSystem::render()
{
	if (!shouldRender) return;
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (const auto& id : gridLayers | std::views::keys)
	{
		renderInternal(id);
	}

	glDisable(GL_BLEND);
}

void GridSystem::onDebugEvent(const OnDebugEventChanged* event)
{
	if (event->key == DebugRenderGrid)
		shouldRender = !shouldRender;
}

TileHolder* GridSystem::getTileHolder(const int id, const glm::ivec2& _pos)
{
	if (_pos.x < 0 || _pos.x > gridSize.x || _pos.y < 0 || _pos.y > gridSize.y)
		return nullptr;

	return gridLayers[id]->internalMap[_pos.x][_pos.y];
}

GridLayer* GridSystem::GetGridLayer(const int id)
{
	return gridLayers[id];
}

Tile* GridSystem::getTile(const int id, const glm::ivec2& _pos)
{
	if (_pos.x < 0 || _pos.x > gridSize.x || _pos.y < 0 || _pos.y > gridSize.y)
		return nullptr;

	return gridLayers[id]->internalMap[_pos.x][_pos.y]->tile;
}

std::vector<std::pair<glm::vec2, Tile*>> GridSystem::getNeighbours(const int id, const glm::vec2 pos)
{
	auto& internalMap = gridLayers[id]->internalMap;
	std::vector<std::pair<glm::vec2, Tile*>> neighbours;
	
	for(int x = -1; x < 2; x++)
	{
		for(int y = -1; y < 2; y++)
		{
			if (x == 0 && y == 0) continue;
			
			glm::vec2 neighbour = pos + glm::vec2(x, y);
			if (neighbour.x < 0 || neighbour.y < 0) continue;
			if (neighbour.x >= gridSize.x || neighbour.y >= gridSize.y) continue;
			
			Tile* tile = internalMap[neighbour.x][neighbour.y]->tile;
			neighbours.emplace_back(neighbour, tile);
		}
	}
	
	return neighbours;
}

std::vector<std::pair<glm::vec2, TileHolder*>> GridSystem::getNeighbours(int id, TileHolder* tile)
{
	auto& internalMap = gridLayers[id]->internalMap;
	std::vector<std::pair<glm::vec2, Tile*>> neighbours;

	for (int x = -1; x < 2; x++)
	{
		for (int y = -1; y < 2; y++)
		{
			if (x == 0 && y == 0) continue;

			glm::vec2 neighbour = pos + glm::vec2(x, y);
			if (neighbour.x < 0 || neighbour.y < 0) continue;
			if (neighbour.x >= gridSize.x || neighbour.y >= gridSize.y) continue;

			Tile* tile = internalMap[neighbour.x][neighbour.y]->tile;
			neighbours.emplace_back(neighbour, tile);
		}
	}

	return neighbours;
}

void GridSystem::loadFromFile(const int mapID, const std::string& fileName)
{
	clearGrid(mapID);
	
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		LOG_ERROR("Failed to open file: " + fileName);
		return;
	}

	std::stringstream buffer;
	buffer << file.rdbuf();
	
	std::string input = buffer.str();
	std::string output;
	std::regex const tab(R"(\t|\n)");

	std::regex_replace(back_inserter(output), std::begin(input), std::end(input), tab, ",");

	input = output;
	std::regex const remove(R"(\0)");
	std::regex_replace(back_inserter(output), std::begin(input), std::end(input), remove, "");

	output.pop_back();
	output.erase(0, 2);
	
	char id;
	std::string curNumber;
	int x = 0, y = gridSize.y - 1;
	
	while (!output.empty())
	{
		id = output.front();
		output.erase(0, 1);
		
		if (id == '\0') continue;
		if (x >= gridSize.x || y < 0) continue;

		if (id == ',')
		{
			int i = std::stoi(curNumber);
			GridLayer* layer = gridLayers[mapID];
			TileHolder* grid_holder = layer->internalMap[x][y];

			if (Texture texture = gridLayers[mapID]->textureMap[i]; texture.Height != 0 && texture.Width != 0)
				grid_holder->tile->SetTexture(texture);

			grid_holder->isOccupied = std::ranges::find(layer->emptyTiles, i) == layer->emptyTiles.end();
			grid_holder->isWall =std::ranges::find(layer->wallIDs, i) != layer->wallIDs.end();
			
			x += 1;
			if (x >= gridSize.x)
			{
				x = 0;
				y -= 1;
			}

			curNumber = "";
		}
		else
		{
			curNumber += id;
		}
	}
}

void GridSystem::setTextureMap(const int id, const std::map<int, Texture>& textureMap)
{
	if (!this->gridLayers.contains(id))
		this->gridLayers[id] = new GridLayer();
		
	this->gridLayers[id]->textureMap = textureMap;
}

void GridSystem::setWallIDs(const int id, const std::vector<int>& wallIDs)
{
	if (!this->gridLayers.contains(id))
		this->gridLayers[id] = new GridLayer();
		
	this->gridLayers[id]->wallIDs = wallIDs;
}

void GridSystem::setEmptyTileIDs(const int id, const std::vector<int>& emptyTileIDs)
{
	if (!this->gridLayers.contains(id))
		this->gridLayers[id] = new GridLayer();
		
	this->gridLayers[id]->emptyTiles = emptyTileIDs;
}


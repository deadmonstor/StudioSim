#include <glad/glad.h>
#include "GridSystem.h"

#include <regex>

#include "Core/Renderer/Renderer.h"
#include "Core/Renderer/ResourceManager.h"
#include "Util/Logger.h"
#include "Util/Events/Events.h"

void GridSystem::init(const glm::fvec2 _tileSize, const glm::ivec2 _gridSize)
{
	tileSize = _tileSize;
	gridSize = _gridSize;
	
	for(int x = 0; x < gridSize.x; x++)
		for(int y = 0; y < gridSize.y; y++)
		{
			GridHolder* grid_holder = internalMap[x][y] = new GridHolder();
			grid_holder->isOccupied = false;

			Tile* tile = new Tile(Texture());
			tile->setSortingLayer(Renderer::getSortingLayer("background"));
			tile->createBuffers();

			internalMap[x][y]->tile = tile;
		}

	// subscribe to the event
	Griddy::Events::subscribe(this, &GridSystem::onDebugEvent);
}

void GridSystem::render()
{
	if (!shouldRender || internalMap.empty()) return;
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	for(auto [x, pointer] : internalMap)
	{
		const auto windowSize = Renderer::getWindowSize();
		
		const float tileWidth = tileSize.x;
		const float tileHeight = tileSize.y;
		
		const float tileX = x * tileWidth;
		
		for(auto [y, holder] : pointer)
		{
			const float tileY = y * tileHeight;
			const auto pos = glm::vec2{tileX, tileY};

			if (!holder->isOccupied) continue;
			
			holder->tile->update();
			
			Renderer::Instance()->renderSprite(holder->tile,
				pos - windowSize / 2.0f,
				{tileWidth, tileHeight},
				0
			);
		}
	}

	glDisable(GL_BLEND);
}

void GridSystem::onDebugEvent(const OnDebugEventChanged* event)
{
	if (event->key == DebugRenderGrid)
		shouldRender = !shouldRender;
}

Tile* GridSystem::getTile(const glm::ivec2& _pos)
{
	return internalMap[_pos.x][_pos.y]->tile;
}

void GridSystem::loadFromFile(const std::string& fileName)
{
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

	// while loop popping off the first character of the string
	while (!output.empty())
	{
		id = output.front();
		output.erase(0, 1);
		
		if (id == '\0') continue;
		if (x >= gridSize.x || y < 0) continue;

		if (id == ',')
		{
			int i = std::stoi(curNumber);
			internalMap[x][y]->tile->SetTexture(textureMap[i]);

			// TODO: Don't hardcode this
			internalMap[x][y]->isOccupied = i != 0;
			
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
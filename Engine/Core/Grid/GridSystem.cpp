#include <glad/glad.h>
#include "GridSystem.h"

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
			std::vector textureList = ResourceManager::GetTexturesContaining("Blue-Slime-Hurt");

			internalMap[x][y] = new GridHolder();
			internalMap[x][y]->tile = new Tile(textureList, 0.075f);
			internalMap[x][y]->tile->setSortingLayer(Renderer::getSortingLayer("background"));
			internalMap[x][y]->tile->createBuffers();
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
			
			internalMap[x][y]->tile->update();
			
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
	
	char c;
	int x = 0, y = gridSize.y - 1;
	while (file.get(c))
	{
		if (c == 'ÿ' || c == 'þ' || c == '\\0' || std::isblank(c) || !std::isdigit(c))
			continue;

		int id = static_cast<int>(c) - 48;
		internalMap[x][y]->tile->textureList =
			std::vector
		{
			textureMap[id],
		};
		
		x += 1;
		if (x >= gridSize.x)
		{
			x = 0;
			y -= 1;
		}
	}
}
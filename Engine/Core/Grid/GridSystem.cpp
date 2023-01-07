#include "GridSystem.h"

#include <glad/glad.h>

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
		const auto windowSize = Renderer::GetWindowSize();
		
		const float cameraX = Renderer::Instance()->GetCameraPos().x;
		const float cameraY = Renderer::Instance()->GetCameraPos().y;
		
		const float tileWidth = tileSize.x;
		const float tileHeight = tileSize.y;
		
		const float tileX = x * tileWidth;
		
		for(auto [y, holder] : pointer)
		{
			const float tileY = y * tileHeight;
			const auto pos = glm::vec2{tileX - cameraX, tileY - cameraY};
			
			internalMap[x][y]->tile->update();
			
			Renderer::Instance()->renderSprite(holder->tile,
				pos - (windowSize / 2.0f),
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

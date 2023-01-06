#include "GridSystem.h"

#include <glad/glad.h>

#include "Core/Renderer/Renderer.h"
#include "Core/Renderer/ResourceManager.h"
#include "Util/Logger.h"

GridSystem::GridSystem()
{
	for(int x = 0; x < 100; x++)
	for(int y = 0; y < 100; y++)
	{
		map[x][y] = new GridHolder();
		
		std::vector<Texture> textureList =
		{
			ResourceManager::GetTexture("BlueSlimeHurt000"),
			ResourceManager::GetTexture("BlueSlimeHurt001"),
			ResourceManager::GetTexture("BlueSlimeHurt002"),
			ResourceManager::GetTexture("BlueSlimeHurt003"),
			ResourceManager::GetTexture("BlueSlimeHurt004"),
			ResourceManager::GetTexture("BlueSlimeHurt005"),
			ResourceManager::GetTexture("BlueSlimeHurt006"),
			ResourceManager::GetTexture("BlueSlimeHurt007"),
			ResourceManager::GetTexture("BlueSlimeHurt008"),
			ResourceManager::GetTexture("BlueSlimeHurt009"),
			ResourceManager::GetTexture("BlueSlimeHurt0010"),
		};
		map[x][y]->tile = new Tile(textureList, 0.05f);
		map[x][y]->tile->createBuffers();
		map[x][y]->tile->SetShader(ResourceManager::GetShader("sprite"));
	}
}
void GridSystem::render()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	for(auto [x, pointer] : map)
	{
		for(auto [y, holder] : pointer)
		{
			map[x][y]->tile->update();
			Renderer::Instance()->rendersprite(reinterpret_cast<SpriteRenderer *>(holder->tile),
				{x * 96, y * 64},
				{96, 64},
				0
			);
		}
	}

	glDisable(GL_BLEND);
}

#pragma once
#include "Util/SingletonTemplate.h"
#include "GridSystem.h"

struct Breadcrumb
{
	int duration;
	Breadcrumb* next;
	glm::vec2 position;

	void tick();
};

class PathfindingMachine : public SingletonTemplate<PathfindingMachine>
{
	std::vector<Tile*> FindPath(glm::vec2 startPos, glm::vec2 endPos);
	int FindTileDistance(glm::vec2 startPos, glm::vec2 endPos);

	void CreateBreadcrumb(glm::vec2 pos);
};


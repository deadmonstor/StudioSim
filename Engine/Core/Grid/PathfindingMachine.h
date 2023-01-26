#pragma once
#include "Util/SingletonTemplate.h"
#include "GridSystem.h"
#include <queue>

//type definition for a Node - allows attaching a heuristic value to each tile holder
typedef std::pair<int, TileHolder*> Node;

class PathfindingMachine : public SingletonTemplate<PathfindingMachine>
{
public:

	//Find tile path between tile pos A and tile pos B
	std::deque<TileHolder*> FindPath(TileHolder* start, TileHolder* end);

	std::deque<TileHolder*> FindPath(glm::vec2 startPos, glm::vec2 endPos);

	//Continues the previously found path to a new position
	std::deque<TileHolder*> ContinuePath(std::deque<glm::vec2> currentPath, TileHolder* end);

	//breadcrumb pathfinding implementation here also
};


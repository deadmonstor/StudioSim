#pragma once
#include "Util/SingletonTemplate.h"
#include "GridSystem.h"
#include <queue>

//type definition for a Node - allows attaching cost to each tile holder
typedef std::pair<int, TileHolder*> Node;

class PathfindingMachine : public SingletonTemplate<PathfindingMachine>
{
private:
	std::map<int, std::map<int, TileHolder*>> pathfindingMap = {};
public:
	//Initialize Variables
	void SetMap(std::map<int, std::map<int, TileHolder*>> pathfindingMapArg) { pathfindingMap = pathfindingMapArg; }

	//Find tile path between tile pos A and tile pos B
	std::deque<TileHolder*> FindPath(TileHolder* start, TileHolder* end);

	//Continues the previously found path to a new position
	std::deque<TileHolder*> ContinuePath(std::deque<glm::vec2> currentPath, TileHolder* end);

	//Finds the tile distance without considering diagonals
	int FindManhattanDistance(glm::vec2 startPos, glm::vec2 endPos);

	//Finds the tile distance using line intersection. This will find a diagonal tile distance
	int FindLineDistance(glm::vec2 startPos, glm::vec2 endPos);
};


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

	//Find tile path between pos A and tile pos B
	std::deque<TileHolder*> FindPath(glm::vec2 startPos, glm::vec2 endPos);

	//Finds the distance without considering diagonals
	float FindManhattanDistance(glm::vec2 startPos, glm::vec2 endPos);

	//Find whether a line intersects a wall between tile A and tile B
	bool LineOfSight(TileHolder* start, TileHolder* end);

	//Find whether a line intersects a wall between point A and point B
	bool LineOfSight(glm::vec2 startPos, glm::vec2 endPos);

	//Estimates the distance between 2 points
	float EstimateDistance(glm::vec2 startPos, glm::vec2 endPos);

	//breadcrumb pathfinding implementation here also
};


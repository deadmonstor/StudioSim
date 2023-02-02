#pragma once
#include "Util/SingletonTemplate.h"
#include "GridSystem.h"
#include <queue>

//type definition for a Node - allows attaching a heuristic value to each tile holder
typedef std::pair<int, TileHolder*> Node;

struct PathfindingData
{
	PathfindingData() { 
		tiles = std::deque<TileHolder*>(); 
		frontier = std::priority_queue<Node, std::vector<Node>, 
			std::greater<Node>>(); cameFromMap = std::unordered_map<TileHolder*, TileHolder*>(); 
		costMap = std::unordered_map<TileHolder*, int>(); found = false;
	}
	//output path to target
	std::deque<TileHolder*> tiles;

	//frontier queue - chooses the next node to inspect
	std::priority_queue<Node, std::vector<Node>, std::greater<Node>> frontier;

	//Map specifying which was the previous tile that was used to find the mapped tile
	std::unordered_map<TileHolder*, TileHolder*> cameFromMap;

	//Maps the total distance to get to a particular tile
	std::unordered_map<TileHolder*, int> costMap;

	bool found;
};

class PathfindingMachine : public SingletonTemplate<PathfindingMachine>
{
public:

	//Find tile path between tile pos A and tile pos B
	PathfindingData FindPath(PathfindingData& dataOut, TileHolder* start, TileHolder* end);

	//Find tile path between pos A and tile pos B
	PathfindingData FindPath(PathfindingData& dataOut, glm::vec2 startPos, glm::vec2 endPos);

	//Finds the distance without considering diagonals
	float FindManhattanDistance(glm::vec2 startPos, glm::vec2 endPos);

	//Find whether a line intersects a wall between tile A and tile B
	bool LineOfSight(TileHolder* start, TileHolder* end);

	//Find whether a line intersects a wall between point A and point B
	bool LineOfSight(glm::vec2 startPos, glm::vec2 endPos);

	//Estimates the distance between 2 points
	float EstimateDistance(glm::vec2 startPos, glm::vec2 endPos);



	TileHolder* FindClosestEmptyTile(TileHolder* start, TileHolder* goal, int maxDepth, int startDepth);
	TileHolder* FindClosestEmptyTile(glm::vec2 startPos, glm::vec2 goalPos, int maxDepth, int startDepth);
	TileHolder* FindClosestEmptyTile(TileHolder* goal, int maxDepth, int startDepth);
	TileHolder* FindClosestEmptyTile(glm::vec2 goalPos, int maxDepth, int startDepth);

	//breadcrumb pathfinding implementation here also
};


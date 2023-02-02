#include "PathfindingMachine.h"
#include <stack>
#include <chrono>

std::deque<TileHolder*> PathfindingMachine::FindPath(TileHolder* start, TileHolder* end)
{
	//frontier queue - chooses the next node to inspect
	std::priority_queue<Node, std::vector<Node>, std::greater<Node>> frontier;

	//Map specifying which was the previous tile that was used to find the mapped tile
	std::unordered_map<TileHolder*, TileHolder*> cameFromMap;

	//Maps the total distance to get to a particular tile
	std::unordered_map<TileHolder*, int> costMap;

	//The path is output to this queue
	std::deque<TileHolder*> path = std::deque<TileHolder*>();

	if (end->isWall || end->gameObjectSatOnTile != nullptr)
	{
		LOG_INFO("Target is an obstructed tile");
		return path;
	}
	if (path.empty()) {
		//Add the start node to frontier
		frontier.push(std::make_pair(0, start));
		costMap[start] = 0;
	}
	else {
		frontier.push(std::make_pair(costMap[path.back()], path.back()));
	}
	bool foundPath = false;

	while (!foundPath && !frontier.empty())
	{
		//Inspect the top node of frontier
		Node currentNode = frontier.top();
		frontier.pop();
		//if the currently inspected node is the target, then the goal has been found
		if (currentNode.second == end)
		{
			foundPath = true;
			break;
		}
		//at the moment uses ID of 0, but make it use a flattened map later
		std::vector<TileHolder*> neighbours = GridSystem::Instance()->getPathfindingNeighbours(0, currentNode.second);
		//Find cost map entries of the neighbours
		for (TileHolder* neighbour : neighbours)
		{
			const bool isWall = GridSystem::Instance()->isWallTile(neighbour->position);
			
			if (isWall || neighbour->isWall || neighbour->gameObjectSatOnTile != nullptr) continue;
			int edgeCost = 1;

			//cost when coming from current node
			int newCost;
			newCost = costMap[currentNode.second] + edgeCost;

			//cost currently stored in the cost map
			int currentCost;
			bool contains = costMap.contains(neighbour);
			if (contains)
			{
				currentCost = costMap[neighbour];
			}
			else
				currentCost = (std::numeric_limits<int>::max)(); //If there is no cost stored, set it to infinity

			//Update cameFromMap and costMap with neighbours
			if (!contains || newCost < currentCost)
			{
				costMap[neighbour] = newCost;
				cameFromMap[neighbour] = currentNode.second;
				int heuristic = FindManhattanDistance(end->position, neighbour->position);
				frontier.push(std::make_pair(heuristic, neighbour));
			}
		}
	}
	if (foundPath)
	{
		path.clear();
		//If the path was found, the queue needs to be created by following the cameFromMap from the target to start
		std::stack<TileHolder*> tempStack;
		TileHolder* queueNode = end;
		while (queueNode != start)
		{
			tempStack.push(queueNode);
			queueNode = cameFromMap[queueNode];
		}
		while (!tempStack.empty())
		{
			path.push_back(tempStack.top());
			tempStack.pop();
		}
	}
	return path;
}

std::deque<TileHolder*> PathfindingMachine::FindPath(glm::vec2 startPos, glm::vec2 endPos)
{
	TileHolder* tile1 = GridSystem::Instance()->getTileHolder(0, startPos / GridSystem::Instance()->getTileSize());
	TileHolder* tile2 = GridSystem::Instance()->getTileHolder(0, endPos / GridSystem::Instance()->getTileSize());
	return FindPath(tile1, tile2);
}

float PathfindingMachine::FindManhattanDistance(glm::vec2 startPos, glm::vec2 endPos)
{
	glm::vec2 directionVec = endPos - startPos;
	return abs(directionVec.x) + abs(directionVec.y);
}

bool PathfindingMachine::LineOfSight(TileHolder* start, TileHolder* end)
{
	int distance = EstimateDistance(start->position, end->position);
	for (int i = 0; i <= distance; i++)
	{
		//Finds the lerp fraction
		float t = (distance == 0) ? 0.0f : float(i) / distance;
		//Interpolates over the line to find intersecting points
		float xlerp = std::lerp(start->position.x, end->position.x, t);
		float ylerp = std::lerp(start->position.y, end->position.y, t);
		xlerp = std::round(xlerp);
		ylerp = std::round(ylerp);
		
		const bool isWall = GridSystem::Instance()->isWallTile(glm::vec2(xlerp, ylerp));
		//If the intersecting tile is a wall, break the function
		if (isWall)
		{
			return false;
		}
	}
	return true;
}


bool PathfindingMachine::LineOfSight(glm::vec2 startPos, glm::vec2 endPos)
{
	TileHolder* tile1 = GridSystem::Instance()->getTileHolder(0, startPos / GridSystem::Instance()->getTileSize());
	TileHolder* tile2 = GridSystem::Instance()->getTileHolder(0, endPos / GridSystem::Instance()->getTileSize());
	if (tile1 == nullptr || tile2 == nullptr)
		return false;
	return LineOfSight(tile1, tile2);
}

float PathfindingMachine::EstimateDistance(glm::vec2 startPos, glm::vec2 endPos)
{
	return std::max(std::abs(endPos.x - startPos.x), std::abs(endPos.y - startPos.y));
}

TileHolder* PathfindingMachine::FindClosestEmptyTile(TileHolder* start, TileHolder* goal, int maxDepth, int startDepth)
{
	//frontier queue - chooses the next node to inspect
	std::priority_queue<Node, std::vector<Node>, std::greater<Node>> frontier;

	//Maps the total distance to get to a particular tile
	std::unordered_map<TileHolder*, int> costMap;

	//Add the goal node to the frontier
	frontier.push(std::make_pair(0, goal));
	costMap[goal] = FindManhattanDistance(start->position, goal->position);
	for (int i = 0; i <= maxDepth; i++)
	{
		//the tiles to inspect on this depth
		std::vector<TileHolder*> tilesToInspect = std::vector<TileHolder*>();

		//while exploring this depth
		while (!frontier.empty() && frontier.top().first == i)
		{
			Node currentNode = frontier.top();

			//Check whether the tile is empty and above the start depth. If so, push it onto inspected tiles
			if (currentNode.second->gameObjectSatOnTile == nullptr && i >= startDepth && !currentNode.second->isWall)
				tilesToInspect.push_back(currentNode.second);

			//Check the neighbours and add them to frontier
			if (i + 1 <= maxDepth)
			{
				std::vector<TileHolder*> neighbours = GridSystem::Instance()->getPathfindingNeighbours(0, currentNode.second);
				for (auto neighbour : neighbours)
				{
					if (!costMap.contains(neighbour))
					{
						costMap[neighbour] = FindManhattanDistance(start->position, neighbour->position);
						frontier.push(std::make_pair(i + 1, neighbour));
					}
				}
			}
			frontier.pop();
		}
		//If there were tiles to inspect, find the best one and output it.
		Node currentBest;
		currentBest.first = std::numeric_limits<int>::max();
		currentBest.second = nullptr;
		for (auto tile : tilesToInspect)
		{
			if (costMap[tile] < currentBest.first)
			{
				currentBest = std::make_pair(costMap[tile], tile);
			}
		}
		if (currentBest.second != nullptr)
		{
			return currentBest.second;
		}
	}
	return nullptr;
}

TileHolder* PathfindingMachine::FindClosestEmptyTile(glm::vec2 startPos, glm::vec2 goalPos, int maxDepth, int startDepth)
{
	TileHolder* tile1 = GridSystem::Instance()->getTileHolder(0, startPos / GridSystem::Instance()->getTileSize());
	TileHolder* tile2 = GridSystem::Instance()->getTileHolder(0, goalPos / GridSystem::Instance()->getTileSize());
	if (tile1 == nullptr || tile2 == nullptr)
		return nullptr;
	return FindClosestEmptyTile(tile1, tile2, maxDepth, startDepth);
}

TileHolder* PathfindingMachine::FindClosestEmptyTile(TileHolder* goal, int maxDepth, int startDepth)
{
	return FindClosestEmptyTile(goal, goal, maxDepth, startDepth);
}

TileHolder* PathfindingMachine::FindClosestEmptyTile(glm::vec2 goalPos, int maxDepth, int startDepth)
{
	TileHolder* tile = GridSystem::Instance()->getTileHolder(0, goalPos / GridSystem::Instance()->getTileSize());
	if (tile == nullptr)
		return nullptr;
	return FindClosestEmptyTile(tile, maxDepth, startDepth);
}

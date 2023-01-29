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

	if (end->isWall)
	{
		LOG_INFO("Target is an obstructed tile");
		return path;
	}

	//Add the start node to frontier
	frontier.push(std::make_pair(0, start));
	costMap[start] = 0;
	bool foundPath = false;

	while (!frontier.empty())
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
			if (neighbour->isWall || neighbour->gameObjectSatOnTile != nullptr) continue;
			int edgeCost = 1;

			//cost when coming from current node
			int newCost;
			newCost = costMap[currentNode.second] + edgeCost;

			//cost currently stored in the cost map
			int currentCost;
			if (costMap.contains(neighbour))
				currentCost = costMap[neighbour];
			else
				currentCost = (std::numeric_limits<int>::max)(); //If there is no cost stored, set it to infinity

			//Update cameFromMap and costMap with neighbours
			if (!cameFromMap.contains(neighbour) || newCost < currentCost)
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
	else 
	{
		LOG_INFO("Path to target was not found.");
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
	auto startTime = std::chrono::steady_clock::now();
	int distance = FindDiagonalDistance(start->position, end->position);
	for (int i = 0; i <= distance; i++)
	{
		//Finds the lerp fraction
		float t = (distance == 0) ? 0.0f : float(i) / distance;
		//Interpolates over the line to find intersecting points
		float xlerp = std::lerp(start->position.x, end->position.x, t);
		float ylerp = std::lerp(start->position.y, end->position.y, t);
		xlerp = std::round(xlerp);
		ylerp = std::round(ylerp);
		TileHolder* tile = GridSystem::Instance()->getTileHolder(0, glm::vec2(xlerp, ylerp));
		//If the intersecting tile is a wall, break the function
		if (tile->isWall)
		{
			auto finish = std::chrono::steady_clock::now();
			double elapsedSeconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - startTime).count();
			return false;
		}
	}
	auto finish = std::chrono::steady_clock::now();
	double elapsedSeconds = std::chrono::duration_cast<std::chrono::duration<double>>(finish - startTime).count();
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

float PathfindingMachine::FindDiagonalDistance(glm::vec2 startPos, glm::vec2 endPos)
{
	return std::max(std::abs(endPos.x - startPos.x), std::abs(endPos.y - startPos.y));
}

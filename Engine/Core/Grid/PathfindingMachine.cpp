#include "PathfindingMachine.h"
#include <stack>

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
		std::vector<TileHolder*> neighbours = GridSystem::Instance()->getNeighbours(0, currentNode.second);
		//Find cost map entries of the neighbours
		for (TileHolder* neighbour : neighbours) 
		{
			if (neighbour->isWall) continue;
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
				int heuristic = GridSystem::Instance()->FindManhattanTileDistance(end->position, neighbour->position);
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

std::deque<TileHolder*> PathfindingMachine::ContinuePath(std::deque<glm::vec2> currentPath, TileHolder* end)
{
	//check if the new target lies on the current path
	//if it does, shorten the path
	//otherwise, find path from end of current path to new target


	return std::deque<TileHolder*>();
}

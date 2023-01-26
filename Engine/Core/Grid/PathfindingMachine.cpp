#include "PathfindingMachine.h"

std::deque<TileHolder*> PathfindingMachine::FindPath(TileHolder* start, TileHolder* end)
{
	//frontier queue - chooses the next node to inspect
	std::priority_queue<Node, std::vector<Node>, std::greater<Node>> frontier;

	//Map specifying which was the previous tile that was used to find the mapped tile
	std::unordered_map<TileHolder*, TileHolder*> cameFromMap;

	//Maps the total distance to get to a particular tile
	std::unordered_map<TileHolder*, int> cost;

	//The path is output to this queue
	std::deque<TileHolder*> path = std::deque<TileHolder*>();

	//Add the start node to frontier
	frontier.push(std::make_pair(0, start));
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
		std::vector<std::pair<glm::vec2, Tile*>> neighbours = GridSystem::getNeighbours(0, currentNode.second->position);
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

int PathfindingMachine::FindManhattanDistance(glm::vec2 startPos, glm::vec2 endPos)
{
	glm::vec2 directionVec = endPos - startPos;
	return abs(directionVec.x) + abs(directionVec.y);
}

int PathfindingMachine::FindLineDistance(glm::vec2 startPos, glm::vec2 endPos)
{
	return 0;
}

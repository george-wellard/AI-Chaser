#pragma once
#include "SFML/graphics.hpp"
#include "Node.h"
#include "AiMap.h"
#include "Neighbour.h"
#include <list>
#include <vector>
#include <algorithm>

class AStar
{
public:

	AStar(AiMap * map);

	bool possiblePath(Node start, Node goal);

	list<Node>getPath();

private:

	vector<Node*> getNeighbourNodes(Node * node);

	void createPath(std::list<Node>& closed, Node * node);

	list<Node> path;

	AiMap * mapPoint;

	int rows;

	int columns;

};
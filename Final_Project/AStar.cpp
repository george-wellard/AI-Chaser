#include "AStar.h"

AStar::AStar(AiMap * map)
{
	mapPoint = map;
}

bool AStar::possiblePath(Node start, Node goal)
{
	list<Node*> open; // Open Nodes
	list<Node> closed; // Closed nodes
	closed.empty(); // Closed node starts empty
	Node current_node = start; // Setting the current node as the start
	Node goal_node = goal; // Setting the goal node as the goal

	if (current_node.equals(goal_node)) 
	{
		return false; // Checking if the goal node has been reached 
	}
	
	current_node.setGScore(0); // Setting the G score to 0 for new calculations 
	float gCheck = current_node.getGScore();
	current_node.hCalculation(goal_node); // H score calculation looking at the distance between the current node and goal node
	current_node.gCalculation(current_node.getGScore()); // New G score
	current_node.fCalculation(); // F score adding the H and G
	cout << "Start Node : (" << start.getRow() << " " << start.getColumn() << ")" << endl;

	open.push_back(&current_node); // The current node to set to the open list

	while (!open.empty())
	{
		open.sort([](const Node *one, const Node *two) {return one->getFScore() < two->getFScore(); }); // Setting a comparision using a lamda so we can check which node has the lowest F score
		current_node = *open.front(); // The current node is set to the lowest F score of the open list list 

		if (current_node.equals(goal_node)) 
		{
			path.clear(); // Clearing the old path
			createPath(closed, &goal); // Creating a new path based on the closed list for the path and goal node as an end point
			cout << "Goal Node: Row:" << goal.getRow() << ", Column:" << goal.getColumn() << endl;
			return true;
		}

		open.pop_front(); // Smallest f score comes off the open list
		closed.push_back(current_node); // Current node goes to the closed list 
		current_node.setClosed();
		list<Node>::iterator closedIt; // Setting iterator so we can go through the closed list
		list<Node*>::iterator openIt; // Setting iterator so we can go through the open list

		for (Node* &neightbourNode : getNeighbourNodes(&current_node)) // Getting the neighboring nodes around the current node
		{
			bool nodeInClosed = false;

			for (closedIt = closed.begin(); closedIt != closed.end(); ++closedIt) // Iterating through the closed list
			{
				if (neightbourNode->equals(*closedIt)) // Checking the the neighbour nodes are in the closed list
				{
					nodeInClosed = true;
				}
			}

			if (!nodeInClosed) // If the nodes are not in the closed list
			{
				bool nodeInOpen = false;

				for (openIt = open.begin(); openIt != open.end(); ++openIt) // Iterating through the open list
				{
					if (neightbourNode->equals(**openIt)) // Now checking for neighbour nodes in the open list
					{
						nodeInOpen = true;
					}
				}

				neightbourNode->hCalculation(goal_node); // Calculating the h score for neighbours
				neightbourNode->gCalculation(current_node.getGScore()); // Calculating g score for neighbours

				if (!nodeInOpen)
				{
					open.push_back(neightbourNode); // Adding the neighbours to the open list
					neightbourNode->setOpen();
				}
				else
				{
					if (neightbourNode->canImproveG())
					{
						neightbourNode->improveG(); // Improving the G score if possible in order to get the cheapest path
					}
				}
				neightbourNode->fCalculation(); // Final f score calculation
			}
		}
	}
	return false;
}

vector<Node*> AStar::getNeighbourNodes(Node * node)
{
//	int current_node_index = node->getIndex();
	// Getting the current node position 
	int current_node_row = node->getRow();
	int current_node_column = node->getColumn();

	int topLeft = 0; int top = 1; int topRight = 2; int Left = 3; int Right = 4; int bottomLeft = 5; int bottom = 6; int bottomRight = 7;

	/*Neighbour positions
	//   [0][1][2]
	//   [3][C][4]
	//   [5][6][7]*/

	// Going through each neighbor by setting it's position according their row and column away from the current node. Also making sure to set the diagonal boolean appropiately 
	Neighbour topLeftNeighbour(current_node_row - 1, current_node_column - 1, true);
	Neighbour topNeighbour(current_node_row, current_node_column - 1, false);
	Neighbour topRightNeighbour(current_node_row + 1, current_node_column - 1, true);
	Neighbour leftNeighbour(current_node_row - 1, current_node_column, false);
	Neighbour rightNeighbour(current_node_row + 1, current_node_column, false);
	Neighbour bottomLeftNeighbour(current_node_row - 1, current_node_column + 1, true);
	Neighbour bottomNeighbour(current_node_row, current_node_column + 1, false);
	Neighbour bottomRightNeighbour(current_node_row + 1, current_node_column + 1, true);

	// Adding all the neighbours to a vector 
	vector<Neighbour> neighbours;
	neighbours.push_back(topLeftNeighbour);
	neighbours.push_back(topNeighbour);
	neighbours.push_back(topRightNeighbour);
	neighbours.push_back(leftNeighbour);
	neighbours.push_back(rightNeighbour);
	neighbours.push_back(bottomLeftNeighbour);
	neighbours.push_back(bottomNeighbour);
	neighbours.push_back(bottomRightNeighbour);

	vector<Node*> NeighbourNodes;

	for (Neighbour n : neighbours) // Going through all the nieghbours 
	{
		if (mapPoint->mapArray[n.getRow()][n.getColumns()]->checkMoveable()) // Checking if the neighbour nodes can be moved on
		{
			NeighbourNodes.push_back(mapPoint->mapArray[n.getRow()][n.getColumns()]); // Getting the node position for each one
			NeighbourNodes.front()->setDiagonal(n.isDiagonal()); // Setting the nodes as diaginal if they return true 
		}
	}

	return NeighbourNodes;
}

void AStar::createPath(std::list<Node>& closed, Node * node)
{
	list<Node>::iterator graphListIt; // Iterating through the graph
	Node* currentNode = node; // Setting the current node to the goal node
	path.push_front(*currentNode); // Current node becomes the start of a new path

	for (graphListIt = closed.end(), graphListIt--; graphListIt != closed.begin(); --graphListIt) // Iterating through graph
	{
		path.push_front(*graphListIt); // 
		closed.erase(graphListIt); // Removing node from closed list
		graphListIt = closed.end(); // Going backwards through closed list
	}

	for (Node node : path)
	{
		cout << node.getRow() << " " << node.getColumn() << endl;
	}
}


list<Node> AStar::getPath()
{
	return path; // Returning the path for the state machine class to use 
}
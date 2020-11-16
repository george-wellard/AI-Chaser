#include "EnemyStateMachine.h"

EnemyStateMachine::EnemyStateMachine(sf::RenderWindow *window, Player* thePlayer, Hider* theHider, Wall* walls)
{
	enemy = new Enemy(window->getSize()); // Setting a new enemy object for the state machine to work with
	player = thePlayer; // Address for the player
	hider = theHider; // Addreess for the hider
	wall = walls; // Address for the walls
	map = new AiMap(); // Calling in the AI Map
	maxRow = map->rows; // Max row is set to the over number of rows
	maxColumn = map->columns; // Max column is set to the overall number of columns
	centerX = maxRow / 2; // Get the center rwo by dividing the max by two
	centerY = maxColumn / 2; // Get the center column by dividing the max by two
	aStar = new AStar(map); // Calling in the a star
	enemy->clearMovement(); // Clearing movement 
}

// Returning all the pointers

Enemy* EnemyStateMachine::getEnemy()
{
	return enemy;
}

Player* EnemyStateMachine::getPlayer()
{
	return player;
}

Hider* EnemyStateMachine::getHider()
{
	return hider;
}

Wall* EnemyStateMachine::getWall()
{
	return wall;
}

void EnemyStateMachine::runAI() // Function that will be called within the main 
{
	// All the function calls to run the AI
	avoidWalls();

	setCurrentNode();

	trackPlayerNode();

	PathfinderMachine();

	MovementMachine();
}

void EnemyStateMachine::IncreaseLevel()
{
	level++; // Increasing the level by one, which lets the enemy react to the level change
}

void EnemyStateMachine::avoidWalls()
{
	// Setting the edges of the map to be unmoveable nodes
	for (int i = 0; i < maxColumn; i++)
	{
		map->mapArray[0][i]->setWall();
		map->mapArray[maxRow - 1][i]->setWall();
	}
	for (int i = 0; i < maxRow; i++)
	{
		map->mapArray[i][0]->setWall();
		map->mapArray[i][maxColumn - 1]->setWall();
	}

	if (level == 0)
	{
		// Setting the indivual nodes which the wall sprites cover as non-travserable 

		for (int i = 1; i < 7; i++)
		{
			map->mapArray[6][i]->setWall();
		}

		for (int i = 5; i < 18; i++)
		{
			map->mapArray[23][i]->setWall();
		}

		for (int i = 24; i < 29; i++)
		{
			map->mapArray[i][17]->setWall();
		}

		for (int i = 28; i < 35; i++)
		{
			map->mapArray[24][i]->setWall();
		}

		for (int i = 8; i < 15; i++)
		{
			map->mapArray[i][35]->setWall();
		}

		for (int i = 36; i < 40; i++)
		{
			map->mapArray[14][i]->setWall();
		}

		for (int i = 4; i < 11; i++)
		{
			map->mapArray[i][28]->setWall();
		}
	}

	else if (level == 1)
	{
		// Resetting the walls nodes from the first level back to moveable nodes
		float levelCheck = level; 

		for (int i = 1; i < 7; i++)
		{
			map->mapArray[6][i]->resetWall();
		}

		for (int i = 5; i < 18; i++)
		{
			map->mapArray[23][i]->resetWall();
		}

		for (int i = 24; i < 29; i++)
		{
			map->mapArray[i][17]->resetWall();
		}

		for (int i = 28; i < 35; i++)
		{
			map->mapArray[24][i]->resetWall();
		}

		for (int i = 8; i < 15; i++)
		{
			map->mapArray[i][35]->resetWall();
		}

		for (int i = 36; i < 40; i++)
		{
			map->mapArray[14][i]->resetWall();
		}

		for (int i = 4; i < 11; i++)
		{
			map->mapArray[i][28]->resetWall();
		}

		// Setting the new wall nodes for this level

		for (int i = 7; i < 12; i++)
		{
			map->mapArray[15][i]->setWall();
		}

		for (int i = 3; i < 12; i++)
		{
			map->mapArray[i][17]->setWall();
		}

		for (int i = 29; i < 33; i++)
		{
			map->mapArray[i][5]->setWall();
		}

		for (int i = 17; i < 34; i++)
		{
			map->mapArray[16][i]->setWall();
		}

		for (int i = 8; i < 14; i++)
		{
			map->mapArray[24][i]->setWall();
		}

		for (int i = 17; i < 27; i++)
		{
			map->mapArray[24][i]->setWall();
		}

		for (int i = 6; i < 13; i++)
		{
			map->mapArray[i][34]->setWall();
		}

		for (int i = 25; i < 33; i++)
		{
			map->mapArray[i][34]->setWall();
		}
	}
}

void EnemyStateMachine::setCurrentNode()
{
	// Getting the x and y positions for the enemy 
	float x = enemy->getX() - 8.75f; // We substract this from the x and y values so that the positions can be mapped properly onto a node square 
	float y = enemy->getY() - 8.75f;
	int cNX = (x / 17.5); // Dividing by the map width to get the exact X node
	int cNY = (y / 17.275); // Dividing the the map height to get the exact Y node
	currentNode = map->mapArray[cNY][cNX]; // Storing the values and rows and columns within the map array 
}

void EnemyStateMachine::trackPlayerNode()
{
	// Following the same process as the current node to get the player node
	float x = player->getX() - 8.75f;
	float y = player->getY() - 8.75f;
	int pNX = (x / 17.5);
	int pNY = (y / 17.275);
	playerNode = map->mapArray[pNY][pNX];
}

float EnemyStateMachine::calculateDeltaR(Node * targetNode)
{
	// Getting the difference between the enemy and target positons
	float deltaX = enemy->getX() - targetNode->getX();
	float deltaY = enemy->getY() - targetNode->getY();
	float degree = atan2(deltaY, deltaX) * 180 / PI; // Working out the tangent from these values
	float angle = degree + 180; // Getting the angle by adding 180- 
	float rotation = enemy->getRo(); // Getting the enemy's current rotation
	float deltaR = rotation - angle; // Getting difference from the current rotation 
	return deltaR; // Return the final value for later use
}

void EnemyStateMachine::MovementMachine()
{
	movementState = STILL; // Starting from the still state to stop and see which state to change to
	executePath(); // Moving through the path 
	float targetAngle = 0; // Initilziing target angle
	if (targetNodeSet)
	{
		targetAngle = calculateDeltaR(targetNode); // Setting the angle we want to use 
	}
	int directionThreshold = 7; // A threshold for an acceptable direction 
	bool correctDirection = (targetAngle < directionThreshold && targetAngle > -directionThreshold); // Setting the correct direction to be between the threshold
	bool reachesGoal = (path.size() == 0); // Checking if the path has ended 

	if (movementState = STILL)
	{	
		if (correctDirection && !reachesGoal)
		{
			movementState = MOVE_TOWARD; // If the correct direction is being faced and the goal not yet reached the the AI knows to move towards the goal
		}
		
		else if (!correctDirection && !reachesGoal)
		{
			movementState = ROTATE; // If the correct direction to the node isn't being faced then the AI knows to rotate 
		}
	}

	else if (movementState == MOVE_TOWARD)
	{
		if (reachesGoal)
		{
			movementState = STILL;
		}
	}

	else if (movementState == ROTATE)
	{
		if (correctDirection)
		{
			movementState = MOVE_TOWARD;
		}
	}

	if (reachesGoal)
	{
		pathFound = false; // Resetting path for when the end of the current one is reached 
	}

	runMovementMachine(targetAngle);
}

void EnemyStateMachine::runMovementMachine(float targetAngle)
{
	switch (movementState) // Checking through each state to see if it is in use 
	{
	case MOVE_TOWARD:
	{
		enemy->MoveForwards(); // If this state is in use, the the move forwards function from the enemy class is claled in
	}

	break;

	case MOVE_BACKWARD:
	{
		enemy->MoveBackwards();
	}

	case ROTATE:
	{
		if (targetAngle > 1 && targetAngle < 180) // Checking if the angle to still towards the enemy's left
		{
			enemy->MoveLeft(); // Calling the function to move left if it is the case 
		}

		else if (targetAngle < -1 && targetAngle > -180) // Checking if the angle is still towards the enemy's right
		{
			enemy->MoveRight();
		}

		else if (targetAngle > 180)
		{
			enemy->MoveRight();
		}

		else if (targetAngle < -180)
		{
			enemy->MoveLeft();
		}
	}
	break;

	case STILL:
	{
		enemy->Stop();
	}
	break;

	default:

		break;
	}
}

void EnemyStateMachine::DetectedPlayer()
{
	playerFound = true; // Letting the enemy 

	if (player->getShape().getGlobalBounds().intersects(hider->getShape().getGlobalBounds())) // Checking if the player and hider sprites have collided
	{
		playerFound = false; // Keeping the player undetected 
	}
}
//
bool EnemyStateMachine::checkForPlayer()
{

	if (!player->getShape().getGlobalBounds().intersects(enemy->getDetect()->getShape().getGlobalBounds()))
	{
		return false;
	//	cout << "Player lost" << endl;
	}

	else
	{
		return true;
	};
}

void EnemyStateMachine::PathfinderMachine()
{
	goalHit = goalReached(goalNodeX, goalNodeY); // Checking if the enemy has hit this node meaning it has reached the end of the path

	if (playerFound) // Checking if the player is detectd 
	{
		checkForPlayer(); // An extra check for whether the player is still within the detection zone

		if (true == checkForPlayer()) // If the player is sti
		{
			playerFound = true;
			pathFound = false; // Path is set to false so a new path can be set
			goalHit = false; // Resetting the goal boolean 
			pathfinder = MOVE_TO_PLAYER; // Keeping to the same pathfinder state
		}

		else if (false == checkForPlayer()) // If the player is out of the detection zone
		{
			playerFound = false; // Player is now lost, so set back to false 
			pathFound = false; // Lost path so set to false for new path
			goalHit = false; // Resetting goal boolean
			pathfinder = MOVE_TO_OLD_PATH; // Setting a new pathfinder state to go to next, in this case returning to the start of the old path  
		}

		if (goalHit) // If the enemy has reached the goal 
		{
			playerFound = false; // Player is caught and now respawned, so it is now lost 
			pathFound = false; // Path is finished so the old path is lost to set up the coniditions to create a new one
			goalHit = false; // Goal has been hit, meaning it must be set back to false for the new goal node
			pathfinder = MOVE_TO_OLD_PATH; // New path state now the old one is finished
		}
	}

	// Basically the same process for the movement states 
	if (pathfinder == MOVE_DIAGONALLY)
	{
		if (goalHit)
		{
			pathFound = false;
			goalHit = false;
			pathfinder = MOVE_TO_OP_Y;
		}
	}

	if (pathfinder == MOVE_TO_OP_X)
	{
		if (goalHit)
		{
			pathFound = false; 
			goalHit = false; 
			pathfinder = MOVE_DIAGONALLY;
		}
	}

	if (pathfinder == MOVE_TO_OP_Y)
	{
		if (goalHit)
		{
			pathFound = false;
			goalHit = false;
			pathfinder = MOVE_DIAGONALLY;
		}
	}

	if (pathfinder == MOVE_TO_OLD_PATH)
	{
		if (goalHit)
		{
			pathFound = false;
			goalHit = false;
			pathfinder = MOVE_TO_OP_Y;
		}
	}

	if (pathfinder == MOVE_TO_PLAYER)
	{
		if (goalHit)
		{
			pathFound = false;
			goalHit = false;
			pathfinder = MOVE_TO_OP_Y;
		}
	}

	runPathFinderMachine();
}

void EnemyStateMachine::runPathFinderMachine()
{
	switch (pathfinder) // Going through the cases untill the pathfidning state being used is hit
	{

	case MOVE_TO_OP_X:
	{
		if (enemyLocation("TOP_LEFT")) // Checking if the enemy is in each location
		{
			findPathTo(TOP_RIGHT, MOVE_TO_OP_X); // Depending on the location, a new path is set to a new location using the selected path state
		}

		else if (enemyLocation("TOP_RIGHT"))
		{
			findPathTo(TOP_LEFT, MOVE_TO_OP_X);
		}

		else if (enemyLocation("BOTTOM_RIGHT"))
		{
			findPathTo(BOTTOM_LEFT, MOVE_TO_OP_X);
		}

		else if (enemyLocation("BOTTOM_LEFT"))
		{
			findPathTo(BOTTOM_RIGHT, MOVE_TO_OP_X);
		}
	}
	break;

	case MOVE_TO_OP_Y:
	{
		if (enemyLocation("TOP_LEFT"))
		{
			findPathTo(BOTTOM_LEFT, MOVE_TO_OP_Y);
		}

		else if (enemyLocation("TOP_RIGHT"))
		{
			findPathTo(BOTTOM_RIGHT, MOVE_TO_OP_Y);
		}

		else if (enemyLocation("BOTTOM_RIGHT"))
		{
			findPathTo(TOP_RIGHT, MOVE_TO_OP_Y);
		}

		else if (enemyLocation("BOTTOM_LEFT"))
		{
			findPathTo(TOP_LEFT, MOVE_TO_OP_Y);
		}

		else if (enemyLocation("PLAYER_LOCATION"))
		{
			findPathTo(TOP_LEFT, MOVE_TO_OP_Y);
		}
	}
	break;

	case MOVE_DIAGONALLY:
	{
		if (enemyLocation("TOP_LEFT"))
		{
			findPathTo(BOTTOM_RIGHT, MOVE_DIAGONALLY);
		}

		else if (enemyLocation("TOP_RIGHT"))
		{
			findPathTo(BOTTOM_LEFT, MOVE_DIAGONALLY);
		}

		else if (enemyLocation("BOTTOM_RIGHT"))
		{
			findPathTo(TOP_LEFT, MOVE_DIAGONALLY);
		}

		if (enemyLocation("BOTTOM_LEFT"))
		{
			findPathTo(TOP_RIGHT, MOVE_DIAGONALLY);
		}

		if (enemyLocation("CENTRE"))
		{
			findPathTo(TOP_RIGHT, MOVE_DIAGONALLY);
		}
	}
	break;

	case MOVE_TO_PLAYER:
	{
		path.clear(); // Clearing the old path since this will always occur mid way through the current path
		enemy->clearMovement(); // Clearing the old movement set from the old path
		findPathTo(PLAYER_LOCATION, MOVE_TO_PLAYER); // Finding a path to the player's current location
	}
	break;

	case MOVE_TO_OLD_PATH:
	{
		// Restoring the original values from the previous path state
		bool addPrevX = true; 
		bool addPrevY = true;
		int x = setXNode(zone, addPrevX);
		int y = setYNode(zone, addPrevY);
		runAStar(y, x);
	}
	break;
	}
}

void EnemyStateMachine::findPathTo(mapZone destination, PathFindingState whichState)
{
	bool addPrevXNode; // Keeping tracj of the previous x node
	bool addPrevYNode; // Keeping track of the previouis y node

	switch (whichState)
	{

	case MOVE_TO_PLAYER:
	{
		// Depending on which state, one of the previous nodes can be kept.  
		addPrevXNode = false;
		addPrevYNode = false;

		break;
	}
	case MOVE_DIAGONALLY:
	{
		// Moving diagonally means both nodes have to update, therefore set to false
		addPrevXNode = false;
		addPrevYNode = false;

		break;
	}
	case MOVE_TO_OP_X:
	{
		// Since only the X node needs to update when moving along the x axis, the y node can be kept
		addPrevXNode = false;
		addPrevYNode = true;

		break;
	}
	case MOVE_TO_OP_Y:
	{
		addPrevXNode = true;
		addPrevYNode = false;

		break;
	}
	case MOVE_TO_OLD_PATH:
	{
		addPrevXNode = false;
		addPrevYNode = false;

		break;
	}

	default:
	{
		addPrevXNode = false;
		addPrevYNode = false;
	}
	break;
	}

	// Calling functions to set the x and y nodes
	int x = setXNode(destination, addPrevXNode);
	int y = setYNode(destination, addPrevYNode);
	runAStar(y, x);

	if (whichState != MOVE_TO_OLD_PATH)
	{
		zone = destination; // 
	}
}

int EnemyStateMachine::setXNode(mapZone destination, bool addPrevNode)
{
	int column = currentNode->getColumn();
	switch (destination) // Switching between each set destination until the one in use is reached
	{
	case TOP_LEFT:
	{
		int x;
		// After first checking if previous node is being used, the chosen column for the destination is slightly randomize which node the AI is heading towards when going to that destination within a certain parmeter
		addPrevNode ? x = column + (int)(rand() % 2) : x = (int)(rand() % 2 + 3);
		return x;
	}
	break;

	case BOTTOM_LEFT:
	{
		int x;
		addPrevNode ? x = column + (int)(rand() % 2) : x = (int)(rand() % 2 + 3);
		return x;
	}
	break;

	case TOP_RIGHT:
	{
		int x;
		addPrevNode ? x = column - (int)(rand() % 2) : x = (int)(rand() % 2 + (maxColumn - 3));
		return x;
	}
	break;

	case BOTTOM_RIGHT:
	{
		int x;
		addPrevNode ? x = column - (int)(rand() % 2) : x = (int)(rand() % 2 + (maxColumn - 3));
		return x;
	}
	break;

	case PLAYER_LOCATION:
	{
		int x = playerNode->getColumn(); // Player location is the player's current column 
		return x;
	}

	default:
		break;
	}

	return 0;
}

int EnemyStateMachine::setYNode(mapZone destination, bool addPrevNode)
{
	// Same process as with the x node
	int row = currentNode->getRow();
	switch (destination)
	{
	case TOP_LEFT:
	{
		int y;
		addPrevNode ? y = row + (int)(rand() % 1 - 1) : y = (int)(rand() % 2 + 3);
		return y;
	}
	break;

	case BOTTOM_LEFT:
	{
		int y;
		addPrevNode ? y = row + (int)(rand() % 1 - 1) : y = (int)(rand() % 2 + (maxRow - 3));
		return y;
	}
	break;

	case TOP_RIGHT:
	{
		int y;
		addPrevNode ? y = row + (int)(rand() % 1 - 1) : y = (int)(rand() % 2 + 3);
		return y;
	}
	break;

	case BOTTOM_RIGHT:
	{
		int y;
		addPrevNode ? y = row + (int)(rand() % 1 - 1) : y = (int)(rand() % 2 + (maxRow - 3));
		return y;
	}
	break;

	case PLAYER_LOCATION:
	{
		int y = playerNode->getRow();
		return y;
	}

	default:
		break;
	}

	return 0;
}

void EnemyStateMachine::executePath()
{
	if (path.size() != 0) // Checking if the path still isn't finished 
	{
		targetNode = &path.front(); // sets the target node to the front of the path 
		targetNodeSet = true; // New target is now ready 
		map->mapArray[targetNode->getRow()][targetNode->getColumn()]->setPath(); // Setting colour for the path nodes
		if (targetNode->equals(*currentNode)) // Checking if current node has hit target
		{
			path.pop_front(); // Remove path 
			if (path.size() != 0)
			{
				targetNode = &path.front(); // Target node is set to new path
			}
		}
	}
}

void EnemyStateMachine::runAStar(int x, int y)
{
	int row = x;
	int column = y; 
	while (map->mapArray[row][column]->checkMoveable()==false) // Checking if the row and column is actually one that can be moved on
	{
		// If this is the case then the nodes are shifted by one until they hit moveable nodes
		(row <= centerX) ? row =+ 1 : row =- 1;
		(column <= centerY) ? column =+ 1 : column =- 1;
	}

	while (!pathFound) // If there isn't currently a path set
	{
		path.clear(); // Remove the old path
		if (aStar->possiblePath(*currentNode, *map->mapArray[row][column])) // Run the A star to find a path to the now set goal node
		{
			path = aStar->getPath(); // Setting the path to the A stars
			pathFound = true; // A path is now in place, so the boolean is set to true so the A star only needs to calculate a path again when the path has ended or changed 
			// Setting goal node to the set row and columns
			goalNodeY = row;
			goalNodeX = column;
		}
	}
}

bool EnemyStateMachine::enemyLocation(string position)
{
	int row = currentNode->getRow();
	int column = currentNode->getColumn();
	int playerX = playerNode->getColumn();
	int playerY = playerNode->getRow();

	// Dividing the map into several zones according to what position the current nodes are in against the position of the center x and y nodes
	if (position == "TOP_LEFT")
	{
		return (column < centerX && row < centerY);
	}

	else if (position == "TOP_RIGHT")
	{
		return (column > centerX && row < centerY);
	}

	else if (position == "BOTTOM_LEFT")
	{
		return (column < centerX && row > centerY);
	}

	else if (position == "BOTTOM_RIGHT")
	{
		return (column > centerX && row > centerY);
	}

	else if (position == "CENTRE")
	{
		return (column == centerY && row == centerX);
	}

	else if (position == "PLAYER_LOCATION")
	{
		return (column == playerX && row == playerY); // Player has it's own location which is constantly changing, therefore the current player nodes are used instead
	}

	return false;
}

bool EnemyStateMachine::goalReached(int row, int column)
{
	// Checking if the current node is equal the goal node
	int iRow = currentNode->getRow();
	int iColumn = currentNode->getColumn();
	if ((iColumn == row) && (iRow == column))
	{
		return true;
	}
	return false;
}
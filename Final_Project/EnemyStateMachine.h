#pragma once
#include "SFML/Graphics.hpp"
#include "AStar.h"
#include "AiMap.h"
#include "Node.h"
#include "Enemy.h"
#include "Wall.h"
#include "Player.h"
#include "Hider.h"

class EnemyStateMachine
{
public:

	EnemyStateMachine(sf::RenderWindow *window, Player* thePlayer, Hider* theHider, Wall* walls);

	Enemy* getEnemy();

	Player* getPlayer();

	Hider * getHider();

	Wall * getWall();

	void runAI();

	void IncreaseLevel();

	void avoidWalls();

	void DetectedPlayer();

	bool checkForPlayer();

	AiMap* map;

private:

	Enemy*  enemy;
	Player * player;
	enemyDetection * enemyDetect;
	Hider * hider;
	Wall * wall;

	int maxRow;
	int maxColumn;
	int centerX;
	int centerY;

	float calculateDeltaR(Node * targetNode);

	enum MovementState { ROTATE, MOVE_TOWARD, MOVE_BACKWARD, STILL, COLLISION }; // Using enums to store each state
	MovementState movementState = STILL;
	void MovementMachine();
	void runMovementMachine(float deltaR);

	enum PathFindingState { MOVE_DIAGONALLY, MOVE_TO_OP_Y, MOVE_TO_OP_X, MOVE_TO_PLAYER, MOVE_TO_OLD_PATH };
	PathFindingState pathfinder = MOVE_DIAGONALLY;
	void PathfinderMachine();
	void runPathFinderMachine();

	enum mapZone { TOP_RIGHT, TOP_LEFT, BOTTOM_LEFT, BOTTOM_RIGHT, CENTRE, PLAYER_LOCATION};
	mapZone zone = CENTRE;

	void setCurrentNode();
	void trackPlayerNode();
	void executePath();
	int setXNode(mapZone destination, bool addPrevNode);
	int setYNode(mapZone destination, bool addPrevNode);
	void findPathTo(mapZone destination, PathFindingState whichState);
	void runAStar(int x, int y);
	bool enemyLocation(string position);
	bool goalReached(int row, int column);
	bool goalHit = false;

	AStar * aStar;
	std::list<Node> path; 
	Node* currentNode;
	Node* targetNode;
	Node* playerNode;

	bool targetNodeSet = false;
	bool pathFound = false;  
	bool playerFound = false;
	int level = 0;
	int goalNodeX = 0;
	int goalNodeY = 0; 
};
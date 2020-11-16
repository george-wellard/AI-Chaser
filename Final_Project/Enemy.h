#pragma once
#include "SFML\Graphics.hpp"
#include <iostream>
#include "enemyDetection.h"
#include "EnemyPos.h"
//#include "EnemyStateMachine.h"

using namespace std;

class Enemy
{
public:

	Enemy(sf::Vector2u size);

	void Draw(sf::RenderWindow *window) const;

	void addDetect();

	Enemy Movement();

	void MoveForwards();

	void MoveBackwards();

	void MoveRight();

	void MoveLeft();

	void Stop();

	float getX() const { return currentEnemyPos.getX(); } // Getting the current positions which are stored in Enemy Pos

	float getY() const { return currentEnemyPos.getY(); }

	float getRo() const { return currentEnemyPos.getRo(); }

	enemyDetection* getDetect();

	sf::Sprite getShape();

	void clearMovement();

	EnemyPos currentEnemyPos; // Having a seperate copy of the values just for the enemy sprite to work with 

	float newX;
	float newY;
	float newRo;

private:

	sf::Sprite enemy;
	sf::Texture enemyT;
	float pX;
	float pY;

	enemyDetection * enemyDetect = nullptr; 

	float moveSpeed; 

	

protected:

	bool forward = false;
	bool backward = false;
	bool right = false;
	bool left = false;
};
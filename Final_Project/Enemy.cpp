#include"Enemy.h"
#include<iostream>

Enemy::Enemy(sf::Vector2u size)
{
	if (!enemyT.loadFromFile("res/img/enemy.png"))
	{
		cout << "Enemy load failed" << endl;
	}

//	Setting the starting enemy values
	enemy.setTexture(enemyT);
	enemy.setPosition(350, 200);
	enemy.setOrigin(enemy.getGlobalBounds().width / 2, enemy.getGlobalBounds().height / 2);
	enemy.setRotation(0.0f);

	currentEnemyPos.set(enemy.getPosition().x, enemy.getPosition().y, enemy.getRotation()); // Setting the position object by the initial position values 
}

void Enemy::Draw(sf::RenderWindow *window) const
{
//	enemyDetect->Draw(window);
	window->draw(enemy);
}

void Enemy::addDetect()
{
	// Getting the current sprite positions 
	pX = enemy.getPosition().x;
	pY = enemy.getPosition().y;


	// avoid leaking memory
	if (enemyDetect)
	{
		delete enemyDetect;
	}

	enemyDetect = new enemyDetection(pX, pY); // Setting a new Detection object onto the updated posiitons 
}


Enemy Enemy::Movement()
{
	moveSpeed = 0.3f;
	float x, y, Ro;
	// Getting the current positions 
	x = currentEnemyPos.getX();
	y = currentEnemyPos.getY(); 
	Ro = currentEnemyPos.getRo();
	float RoRad = DEG2RAD(Ro); // Setting the rotation value to radians 
	// New x and y values that are updated by the speed
	float dx = cos(RoRad) * moveSpeed; 
	float dy = sin(RoRad) * moveSpeed;

	// Depending on which function has been called in state machine, the movement direction is activated according to which boolean has been set to true

	if (forward)
	{
		currentEnemyPos.set(x + dx, y + dy, Ro); // Setting the new positions by updating them with the new position values 
	}

	if (backward)
	{
		currentEnemyPos.set(x - dx, y - dy, Ro);
	}

	if (left)
	{
		float newRo = Ro - moveSpeed; // Creating a new rotation value by updating it with the movmement speed
		if (newRo < 0) // Checking if the new value has gone over the full rotation point 
		{
			newRo += 360.0; // Resetting the rotation so that it can keep updating 
		}
		currentEnemyPos.set(x, y, newRo); // Setting the new rotation value  
	}

	if (right)
	{
		float newRo = Ro + moveSpeed;
		if (newRo > 360.0)
		{
			newRo -= 360.0;
		}
		currentEnemyPos.set(x, y, newRo);
	}

	// Updating the sprite by the new positions 
	enemy.setPosition(currentEnemyPos.getX(), currentEnemyPos.getY()); 
	enemy.setRotation(currentEnemyPos.getRo());
	// Checking if the positions have updated correctly
	newX = enemy.getPosition().x;
    newY = enemy.getPosition().y;
	newRo = enemy.getRotation();

	return *this; // Returning the values for the state machine to read from 
}

void Enemy::MoveForwards()
{
	clearMovement(); // Clearing old movement so new movement can be used
	forward = true; // Setting to true so the movement function knows which type of movement it's executing 
}

void Enemy::MoveBackwards()
{
	clearMovement();
	backward = true;
}

void Enemy::MoveRight()
{
	clearMovement();
	right = true;
}

void Enemy::MoveLeft()
{
	clearMovement();
	left = true; 
}

void Enemy::Stop()
{
	clearMovement();
}

enemyDetection* Enemy::getDetect()
{
	return enemyDetect;
}

sf::Sprite Enemy::getShape()
{
	return enemy;
}

void Enemy::clearMovement() // Stopping all movement 
{
	forward = false;
	backward = false;
	right = false;
	left = false;
}

#pragma once
#include"SFML\Graphics.hpp"
#include"Player.h"
//#include"Enemy.h"

using namespace std;

class enemyDetection
{
public:

	enemyDetection(float xPos, float yPos);

	void Detected();

	sf::CircleShape getShape();

private:

	sf::CircleShape enemyDetect;

};
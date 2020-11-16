#include "enemyDetection.h"
#include <iostream>

enemyDetection::enemyDetection(float xPos, float yPos)
{
	enemyDetect.setRadius(100);
	enemyDetect.setFillColor(sf::Color::Cyan);
	enemyDetect.setPosition(xPos, yPos);
	enemyDetect.setOrigin(enemyDetect.getGlobalBounds().width / 2, enemyDetect.getGlobalBounds().height / 2);
}

void enemyDetection::Detected()
{
	cout << "Player is detected" << endl;
}

sf::CircleShape enemyDetection::getShape()
{
	return enemyDetect;
}

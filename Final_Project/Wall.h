#pragma once
#include "SFML\Graphics.hpp"
#include "EnemyPos.h"
#include <iostream>

using namespace std;

class Wall
{
public:

	Wall();

	void setSizeAndPos(float sizeX, float sizeY, float posX, float posY);



	void Draw(sf::RenderWindow *window);

	sf::RectangleShape getShape();

private:

	sf::RectangleShape wall;

	sf::Texture wallT;
};
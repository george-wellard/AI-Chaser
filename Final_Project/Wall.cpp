#include "Wall.h"
#include <iostream>

Wall::Wall()
{
	if (!wallT.loadFromFile("res/img/wall.png"))
	{
		cout << "Wall load failed" << endl;
	}

	wall.setTexture(&wallT);
}

void Wall::setSizeAndPos(float sizeX, float sizeY, float posX, float posY)
{
	wall.setSize(sf::Vector2f(sizeX, sizeY));
	wall.setPosition(posX, posY);
}

void Wall::Draw(sf::RenderWindow *window)
{
	window->draw(wall);
}

sf::RectangleShape Wall::getShape()
{
	return wall;
}

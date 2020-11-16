#include "Background.h"
#include <iostream>

Background::Background(sf::Vector2u size)
{
	if (!floorT.loadFromFile("res/img/floor.png"))
	{
		cout << "Floor load failed" << endl;
	}

	floor.setTexture(floorT);
	floor.setPosition(0.0f, 0.0f);
	floor.setScale(sf::Vector2f(1.5, 1.5));
}

void Background::draw(sf::RenderWindow *window)
{
	window->draw(floor);
}

#pragma once
#include "SFML\Graphics.hpp"

using namespace std; 

class Door
{
public:

	Door(sf::Vector2u size);

	void setSizeAndPos(float sizeX, float sizeY, float posX, float posY);

	void Draw(sf::RenderWindow *window);

	void Open(sf::Event event);

	sf::RectangleShape getShape();

private:

	sf::RectangleShape door;
};
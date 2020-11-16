#include "Door.h"

Door::Door(sf::Vector2u size)
{
	door.setFillColor(sf::Color::White);
}

void Door::setSizeAndPos(float sizeX, float sizeY, float posX, float posY)
{
	door.setSize(sf::Vector2f(sizeX, sizeY));
	door.setPosition(posX, posY);
}

void Door::Draw(sf::RenderWindow *window)
{
	window->draw(door);
}

void Door::Open(sf::Event event)
{
	door.rotate(90.f);
}

sf::RectangleShape Door::getShape()
{
	return door;
}

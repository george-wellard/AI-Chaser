#include "WinZone.h"

WinZone::WinZone()
{
	zone.setSize(sf::Vector2f(50, 50));
	zone.setPosition(0, 0);
	zone.setFillColor(sf::Color::Black);
}

void WinZone::draw(sf::RenderWindow * window)
{
	window->draw(zone);
}

sf::RectangleShape WinZone::getShape()
{
	return zone;
}

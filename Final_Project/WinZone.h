#pragma once
#include "SFML/Graphics.hpp"

class WinZone
{
public:

	WinZone();

	void draw(sf::RenderWindow *window);

	sf::RectangleShape getShape();

private:

	sf::RectangleShape zone;

};
#include "Hider.h"

Hider::Hider(sf::Vector2u size)
{
	if (!hiderT.loadFromFile("res/img/Hider.png"))
	{
		std::cout << "hider load failed" << std::endl;
	}

	hider.setTexture(hiderT);
	hider.setPosition(510, 350);
}

void Hider::draw(sf::RenderWindow *window)
{
	window->draw(hider);
}

sf::Sprite Hider::getShape()
{
	return hider;
}

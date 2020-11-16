#include "Key.h"
#include <iostream>

Key::Key(sf::Vector2u size)
{
	if (!keyT.loadFromFile("res/img/key.png"))
	{
		cout << "Key load failed" << endl;
	}
	
	//key.setSize(sf::Vector2f(25.f, 25.f));
	key.setTexture(keyT);
	key.setPosition(680, 180);
}

void Key::Draw(sf::RenderWindow *window)
{
	window->draw(key);
}

void Key::Disappear(sf::Vector2u size)
{
	key.setPosition(760, 0); // Giving the key a new position off the map once the player has acollectde it 
}

sf::Sprite Key::getShape()
{
	return key;
}

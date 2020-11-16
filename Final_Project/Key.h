#pragma once
#include "SFML\Graphics.hpp"

using namespace std;

class Key
{
public:

	Key(sf::Vector2u size);

	void Draw(sf::RenderWindow *window);

	void Disappear(sf::Vector2u size);

	sf::Sprite getShape();

private:

	sf::Sprite key;
	sf::Texture keyT;
};
#pragma once
#include "SFML\Graphics.hpp"

using namespace std;

class Background
{

public:

	Background(sf::Vector2u size);

	void draw(sf::RenderWindow *window);

private:

	sf::Sprite floor; 
	sf::Texture floorT;
};
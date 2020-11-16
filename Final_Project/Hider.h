#pragma once
#include"SFML/Graphics.hpp"
#include<iostream>

class Hider
{
public:

	Hider(sf::Vector2u size);

	void draw(sf::RenderWindow *window);

	sf::Sprite getShape();

private:

	sf::Sprite hider;
	sf::Texture hiderT;
};
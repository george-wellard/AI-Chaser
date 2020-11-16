#pragma once
#include "SFML\Graphics.hpp"
#include "EnemyPos.h"

using namespace std; 

class Player
{
public:

	Player();

	Player(sf::Vector2u size);

	void Draw(sf::RenderWindow *window);

	Player Move(sf::Event event);

	void Stop(sf::Event event);

	void Death(sf::Vector2u size);

	// Getting the positions from the Position class 
	float getX() const { return currentPlayerPos.getX(); }

	float getY() const { return currentPlayerPos.getY(); }

	float getRo() const { return currentPlayerPos.getRo(); }

	sf::Sprite getShape();

	EnemyPos currentPlayerPos; // Copy of position class just for the player values 

private:

	sf::Sprite player;
	sf::Texture playerT;
	sf::IntRect playerCut = sf::IntRect(0, 0, 50, 46); // Setting parmeters in which a rectangle is cut out of the sprite sheet 
	sf::Clock clock;
};
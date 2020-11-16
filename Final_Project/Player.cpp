#include <iostream>
#include"Player.h"


Player::Player()
{
}

Player::Player(sf::Vector2u size)
{
	if (!playerT.loadFromFile("res/img/playerSpriteSheet.png"))
	{
		cout << "Player load failed" << endl;
	}

	player = sf::Sprite(playerT, playerCut);
	player.setPosition(150, 550);
	player.setTextureRect(playerCut);
	player.setOrigin(sf::Vector2f(player.getGlobalBounds().width / 2, player.getGlobalBounds().height / 2));
	player.setRotation(0.0);

	currentPlayerPos.set(player.getPosition().x, player.getPosition().y, player.getRotation()); // 
}

void Player::Draw(sf::RenderWindow *window)
{
	window->draw(player);
}

Player Player::Move(sf::Event event)
{

	// Using the key codes to set the movement and rotation a certain way according to which key has been pressed 
	if (sf::Keyboard::Key::Right == event.key.code)
	{
		player.move(5.0f, 0.0f);
		player.setRotation(0.0);
		player.rotate(0.0f);
	}

	if (sf::Keyboard::Key::Left == event.key.code)
	{
		player.move(-5.0f, 0.0f);
		player.setRotation(0.0);
		player.rotate(180.0f);
	}

	if (sf::Keyboard::Key::Down == event.key.code)
	{
		player.move(0.0f, 5.0f);
		player.setRotation(0.0);
	    player.rotate(90.0f);
	}

	if (sf::Keyboard::Key::Up == event.key.code)
	{
		player.move(0.0f, -5.0f);
		player.setRotation(0.0);
		player.rotate(270.f);
	}

	/*if (sf::Keyboard::Key::Up && sf::Keyboard::Key::Right == event.key.code)
	{
		player.move(5.0f, -5.0f);
		player.setRotation(0.0);
		player.rotate(45.0f);
	}*/

	currentPlayerPos.set(player.getPosition().x, player.getPosition().y, player.getRotation());
	player.setPosition(currentPlayerPos.getX(), currentPlayerPos.getY());
	player.setRotation(currentPlayerPos.getRo());

	if (clock.getElapsedTime().asSeconds() > 0.4f)
	{
		if (playerCut.left == 150)
		{
			playerCut.left = 0; 
		}
		else
		{
			playerCut.left += 50;
		}

		player.setTextureRect(playerCut);
		clock.restart();
	}

	float xTest = player.getPosition().x;
	float yTest = player.getPosition().y;
	float roTest = player.getRotation();

	return *this;
}

void Player::Stop(sf::Event event)
{
	// Movement is set to zero if player cannot move towards a certain position 

	if (sf::Keyboard::Key::Right == event.key.code)
	{
		player.move(-5.0f, 0.0f);
	}
	
	if (sf::Keyboard::Key::Left == event.key.code)
	{
		player.move(5.0f, 0.0f);
	}

	if (sf::Keyboard::Key::Down == event.key.code)
	{
		player.move(0.0f, -5.0f);
	}

	if (sf::Keyboard::Key::Up == event.key.code)
	{
		player.move(0.0f, 5.0f);
	}

}

void Player::Death(sf::Vector2u size)
{
	player.setPosition(150, 550); // Resetting player back to the start 
}

sf::Sprite Player::getShape()
{
	return player;
}
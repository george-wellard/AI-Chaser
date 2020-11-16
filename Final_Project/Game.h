#pragma once
#include"SFML\Graphics.hpp"
#include"Player.h"
#include "Wall.h"
#include "Key.h"
#include "EnemyStateMachine.h"
#include "Door.h"
#include "Background.h"
#include "WinZone.h"

class Game 
{
public:

	Game();

	void Loop();

	void Draw(); 

	void loadLevel1();

	void loadLevel2();

private:
	sf::RenderWindow *window;

	Player *player;
	Wall *wall;
	Key *key;
	//enemyDetection *enemyDetect{ nullptr };
	Door *door;
	EnemyStateMachine *npc;
	Hider *hider; 
	Background *background; 
	WinZone *zone; 

	sf::Text text;
	sf::Font font;

	const int iWall = 15;

};
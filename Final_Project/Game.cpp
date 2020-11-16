#include "Game.h"

Game::Game()
{

	window = new sf::RenderWindow(sf::VideoMode(740, 600), "PRISON BREAK!");

	player = new Player(window->getSize());
	wall = new Wall[iWall];
	key = new Key(window->getSize());
	//enemyDetect = new enemyDetection(0,0);
	door = new Door(window->getSize());
	background = new Background(window->getSize());
	hider = new Hider(window->getSize());
	npc = new EnemyStateMachine(window, player, hider, wall);
	zone = new WinZone();

	// Setting text for objective UI
	if (!font.loadFromFile("res/Fonts/American Captain.ttf"))
	{
		cout << "No font" << endl;
	};
	text.setFont(font);
	text.setString("Find the key!");
	text.setCharacterSize(30);
	text.setFillColor(sf::Color::White);

	loadLevel1(); // Calling first level 
}

void Game::Loop() 
{
	while (window->isOpen())
	{
		window->clear();

		sf::Event event;
		// handle events

		while (window->pollEvent(event))
		{
			switch (event.type)
			{

			case sf::Event::Closed:
				window->close();

				break;

			case::sf::Event::KeyPressed:
				player->Move(event);

				break;

			}
		}

		// Game Logic
		npc->getEnemy()->addDetect();
		npc->runAI();
		npc->getEnemy()->Movement();

		// Checking for collisions through sprite global bound intersections 
		if (player->getShape().getGlobalBounds().intersects(npc->getEnemy()->getShape().getGlobalBounds()))
		{
			player->Death(window->getSize());
		}

		if (player->getShape().getGlobalBounds().intersects(key->getShape().getGlobalBounds()))
		{
			door->Open(event);
			key->Disappear(window->getSize());
			text.setString("Get to the escape!");
		}

		if (player->getShape().getGlobalBounds().intersects(npc->getEnemy()->getDetect()->getShape().getGlobalBounds()))
		{
			npc->DetectedPlayer();
		}

		for (size_t i = 0; i < iWall; i++)
		{
			if (player->getShape().getGlobalBounds().intersects(wall[i].getShape().getGlobalBounds()))
			{
				player->Stop(event);
			}
		}

		if (player->getShape().getGlobalBounds().intersects(door->getShape().getGlobalBounds()))
		{
			player->Stop(event);
		}

		if (player->getShape().getGlobalBounds().intersects(zone->getShape().getGlobalBounds()))
		{
			loadLevel2();
			npc->IncreaseLevel();
		}

		sf::View view(sf::Vector2f(player->getShape().getPosition().x, player->getShape().getPosition().y), sf::Vector2f(400.f, 300.f)); // Creating camera parmeters 

		window->setView(view); // Setting camera

		text.setPosition(player->getShape().getPosition().x, player->getShape().getPosition().y - 150); // Setting 

		// Draw
		background->draw(window);
	//	npc->map->Draw(window);
		player->Draw(window);
		hider->draw(window);
		key->Draw(window);
		npc->getEnemy()->Draw(window);
		//zone->draw(window);
		for (size_t i = 0; i < iWall; i++)
		{
			wall[i].Draw(window);
		}
		door->Draw(window);
		window->draw(text);

		window->display();
	}
}

void Game::Draw()
{
}

void Game::loadLevel1()
{
	// Walls are stored in an array to create 
	wall[0].setSizeAndPos(220, 20, 100, 410);
	wall[1].setSizeAndPos(20, 100, 311, 410);
	wall[2].setSizeAndPos(140, 20, 0, 115);
	wall[3].setSizeAndPos(100, 20, 640, 250);
	wall[4].setSizeAndPos(20, 120, 625, 150);
	wall[5].setSizeAndPos(740, 20, 0, 0);
	wall[6].setSizeAndPos(20, 600, 0, 0);
	wall[7].setSizeAndPos(740, 20, 0, 580);
	wall[8].setSizeAndPos(20, 600, 720, 0);
	wall[9].setSizeAndPos(20, 120, 505, 80);
	wall[10].setSizeAndPos(150, 20, 500, 430);
	wall[11].setSizeAndPos(20, 150, 150, 200);

	door->setSizeAndPos(20, 115, 140, 0);
}

void Game::loadLevel2()
{

	// New positions for walls and objects when the new level is called in 
	wall[0].setSizeAndPos(300, 20, 310, 290);
	wall[1].setSizeAndPos(200, 20, 311, 425);
	wall[2].setSizeAndPos(20, 140, 610, 450);
	wall[3].setSizeAndPos(100, 20, 130, 270);
	wall[4].setSizeAndPos(20, 120, 610, 110);
	wall[5].setSizeAndPos(740, 20, 0, 0);
	wall[6].setSizeAndPos(20, 600, 0, 0);
	wall[7].setSizeAndPos(740, 20, 0, 580);
	wall[8].setSizeAndPos(20, 600, 720, 0);
	wall[9].setSizeAndPos(20, 150, 310, 70);
	wall[10].setSizeAndPos(100, 20, 160, 425);
	wall[11].setSizeAndPos(20, 150, 100, 500);

	door->setSizeAndPos(115, 20, 600, 450);
	//door->getShape().setRotation(270);
}

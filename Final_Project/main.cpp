#include<SFML\Graphics.hpp>
#include "Game.h"

int main()
{
	Game* game = new Game(); // Calling in game function 

	game->Loop(); // Calling in game loop 

	return EXIT_SUCCESS;
}
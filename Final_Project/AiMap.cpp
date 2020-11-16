#include"AiMap.h"

AiMap::AiMap()
{
	// Paramters for the map 
	float width = 17.5;
	float height = 17.275;
	float xBuffer = 15;
	float yBuffer = 13;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			mapArray[i][j] = new Node(xBuffer + width * j, yBuffer + height * i, width, height, i, j); // Each point of the array represents a node 
		}
	}
}

void AiMap::Draw(sf::RenderWindow *window)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			mapArray[i][j]->drawNode(*window);
		}
	}
}

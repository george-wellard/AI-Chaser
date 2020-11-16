#pragma once
#include "SFML\Graphics.hpp"
#include "Node.h"
#include <list>
#include <vector>
#include <iostream>

using namespace std;

class AiMap
{
public:

	AiMap();

	void Draw(sf::RenderWindow *window);

	static const short unsigned rows = 33;
	static const short unsigned columns = 41;

	Node * mapArray[rows][columns];

private:

};

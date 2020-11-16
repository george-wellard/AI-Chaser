#pragma once
#include"SFML\Graphics.hpp"

using namespace std;

class GameObject
{
public:

	GameObject(int xPosInt, int yPosInt); 

	GameObject();

//	void setWidth(int width);+

//	void setHeight(int height);

	void setxPos(int xPos);

	void setyPos(int yPos);

//	int getWidth();

//	int getHeight();

	int getxPos();

	int getyPos();


private:

	int width;
	int height;
	int xPos;
	int yPos;
};
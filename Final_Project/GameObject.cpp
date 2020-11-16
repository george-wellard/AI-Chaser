#include"GameObject.h"

GameObject::GameObject(int xPosInt, int yPosInt)
{
	/*width = widthInt;
	height = heightInt;*/
	xPos = xPosInt;
	yPos = yPosInt;

}

GameObject::GameObject()
{
}

//void GameObject::setWidth(int width)
//{
//	this->width = width;
//}
//
//void GameObject::setHeight(int height)
//{
//	this->height = height;
//}

void GameObject::setxPos(int xPos)
{
	this->xPos = xPos;
}

void GameObject::setyPos(int yPos)
{
	this->yPos = yPos;
}

//int GameObject::getWidth()
//{
//	return width;
//}
//
//int GameObject::getHeight()
//{
//	return height;
//}

int GameObject::getxPos()
{
	return xPos;
}

int GameObject::getyPos()
{
	return yPos;
}

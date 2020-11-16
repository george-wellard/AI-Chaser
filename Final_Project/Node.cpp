#include "Node.h"

Node::Node()
{
}

Node::Node(float xPosIn, float yPosIn, float heightIn, float widthIn, int rowIn, int columnIn)
{
	xPos = xPosIn;
	yPos = yPosIn;
	row = rowIn; 
	column = columnIn;
	height = heightIn;
	width = widthIn;
	current = false; 
	diagonal = false;
	canMove = true;

	node.setSize(sf::Vector2f(width, height));
	node.setPosition(sf::Vector2f(xPos, yPos));
	node.setFillColor(sf::Color(255, 255, 255, 50));
	node.setOutlineThickness(1);
	node.setOutlineColor(sf::Color(255, 255, 255, 100));
}

void Node::drawNode(sf::RenderWindow & window)
{
	window.draw(node);
}

void Node::setWall()
{
	canMove = false; 
	node.setFillColor(sf::Color(100, 255, 255, 50));
}

void Node::resetWall()
{
	canMove = true; 
	node.setFillColor(sf::Color(100, 150, 150, 50));
}

void Node::setPath()
{
	node.setFillColor(sf::Color(255, 255, 255, 50));
}

void Node::setOpen()
{
	node.setFillColor(sf::Color(200, 100, 100, 50));
}

void Node::setClosed()
{
	node.setFillColor(sf::Color(100, 150, 150, 50));
}

void Node::setRow(int row)
{
	this->row = row;
}

void Node::setColumn(int column)
{
	this->column = column;
}

void Node::setGScore(float value)
{
	this->g = value;
}

void Node::setDiagonal(bool diagonal)
{
	this->diagonal = diagonal;
}

float Node::getFScore() const
{
	return f;
}

float Node::getGScore() const
{
	return g;
}

float Node::getHScore() const
{
	return h;
}

int Node::getX() const
{
	return xPos + width / 2;
}

int Node::getY() const
{
	return yPos + height / 2; 
}

int Node::getRow() const
{
	return row;
}

int Node::getColumn() const
{
	return column;
}

bool Node::checkDiagonal()
{
	return diagonal;
}

bool Node::checkMoveable()
{
	return canMove;
}

bool Node::equals(Node & newNode)
{
	return (row == newNode.getRow() && column == newNode.getColumn());
}

void Node::fCalculation()
{
	f = g + h;
}

void Node::hCalculation(Node & goalNode)
{
	int goalX = goalNode.getX();
	int goalY = goalNode.getY();
	float dx, dy;

	dx = (float)(goalX - xPos);
	dy = (float)(goalY - yPos);
	h = sqrt(dx * dx + dy * dy); // Getting the squre root to return a single value 
}

void Node::gCalculation(float parentGScore)
{
	if (firstGCal)
	{
		// 1.414 is for diagonal nodes
		diagonal ? g = parentGScore + 1.414f : g = parentGScore + 1.0f;

		diagonal ? new_g = parentGScore + 1.414f : new_g = parentGScore + 1.0f;
		firstGCal = false;
	}
	else
	{
		diagonal ? new_g = parentGScore + 1.414f : new_g = parentGScore + 1.0f;
	}
}

bool Node::canImproveG()
{
	return g >= new_g;
}

void Node::improveG()
{
	this->g = new_g;
}
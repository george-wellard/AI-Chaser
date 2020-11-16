#pragma once
#include "SFML\Graphics.hpp"

class Node
{
public:

	Node();

	Node(float xPosIn, float yPosIn, float heightIn, float widthIn, int rowIn, int columnIn);

	void drawNode(sf::RenderWindow &window);

	bool current = true; 

	// drawing
	void setWall();

	void resetWall();

	void setPath();

	void setOpen();

	void setClosed();

	// setting

	void setRow(int row);

	void setColumn(int column);

	void setGScore(float value);

	void setDiagonal(bool diagonal);

	//getting
	float getFScore() const;
	
	float getGScore() const;
	
	float getHScore() const;

	int getX() const;

	int getY() const;

	int getRow() const;

	int getColumn() const;

	bool checkDiagonal();

	bool checkMoveable(); 

	// Calculations for path finding
	bool equals(Node &newNode);

	void fCalculation();

	void hCalculation(Node &goalNode);

	void gCalculation(float parentGScore);

	bool canImproveG();

	void improveG();

private:

	int xPos;
	int yPos;
	int width;
	int height;
	int row;
	int column;

	float f;
	float g;
	float h;
	float new_g;

	bool firstGCal;
	bool diagonal;
	bool canMove; 

	sf::RectangleShape node;
};
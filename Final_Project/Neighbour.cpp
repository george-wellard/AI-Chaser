#include "Neighbour.h"

Neighbour::Neighbour(int row, int column, bool diagonal)
{
	this->row = row;
	this->columns = column;
	this->diagonal = diagonal;
}

bool Neighbour::canMove()
{
	return exists;
}

int Neighbour::getRow()
{
	return row;
}

int Neighbour::getColumns()
{
	return columns;
}

bool Neighbour::isDiagonal()
{
	return diagonal;
}
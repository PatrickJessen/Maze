#include "Cell.h"
#include <iostream>

void Cell::AddDirection(uint8_t value)
{
	this->value = value;

	// If there is not a wall add it to the list
	if (~value & (uint8_t)Direction::NORTH)
		openDirections.push_back(Direction::NORTH);
	if (~value & (uint8_t)Direction::SOUTH)
		openDirections.push_back(Direction::SOUTH);
	if (~value & (uint8_t)Direction::EAST)
		openDirections.push_back(Direction::EAST);
	if (~value & (uint8_t)Direction::WEST)
		openDirections.push_back(Direction::WEST);

	CheckForDeadEnd();
}

void Cell::CheckForDeadEnd()
{
	if (openDirections.size() <= 1)
		isDeadEnd = true;
}

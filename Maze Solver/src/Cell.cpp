#include "Cell.h"
#include <iostream>

void Cell::PlaceWall(uint8_t value)
{
	this->value = value;
	// Check if there is a wall at the given direction
	if (value & (uint8_t)Direction::NORTH)
		walls[Direction::NORTH] = true;
	if (value & (uint8_t)Direction::SOUTH)
		walls[Direction::SOUTH] = true;
	if (value & (uint8_t)Direction::EAST)
		walls[Direction::EAST] = true;
	if (value & (uint8_t)Direction::WEST)
		walls[Direction::WEST] = true;

	CheckForDeadEnd();
}

void Cell::CheckForDeadEnd()
{
	if (walls[Direction::NORTH] && walls[Direction::SOUTH] && walls[Direction::EAST] || walls[Direction::NORTH] && walls[Direction::SOUTH] && walls[Direction::WEST] ||
		walls[Direction::SOUTH] && walls[Direction::EAST] && walls[Direction::WEST] || walls[Direction::NORTH] && walls[Direction::WEST] && walls[Direction::EAST])
		isDeadEnd = true;
	//std::cout << isDeadEnd << "\n";
}

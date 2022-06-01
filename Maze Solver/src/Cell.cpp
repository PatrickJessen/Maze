#include "Cell.h"

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
}

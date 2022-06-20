#pragma once
#include <cstdint>
#include <map>

// 00000001 = North = 1
// 00000010 = South = 2
// 00000100 = East = 4
// 00001000 = West = 8
enum class Direction
{
	NORTH = 1, SOUTH = 2, EAST = 4, WEST = 8
};

class Cell
{
public:
	Cell() = default;

	void PlaceWall(uint8_t value);

private:
	void CheckForDeadEnd();
public:
	uint8_t value;
	std::map<Direction, bool> walls{ {Direction::NORTH, false}, {Direction::SOUTH, false}, {Direction::EAST, false}, {Direction::WEST, false} };
	bool visited = false;
	bool isDeadEnd = false;
};
#pragma once
#include <cstdint>
#include <vector>

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

	void AddDirection(uint8_t value);

private:
	// If we got 1 or less walls in our list, then it must be a dead end
	void CheckForDeadEnd();
public:
	uint8_t value;
	std::vector<Direction> openDirections;
	bool visited = false;
	bool isDeadEnd = false;
};
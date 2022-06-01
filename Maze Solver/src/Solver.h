#pragma once
#include "Maze.h"
#include <vector>
#include <string>

class Solver
{
public:
	Solver(Maze* maze);
	~Solver() = default;

public:
	void Solve();

private:
	// Helper function that checks where the walls are and if a cell has already been visited
	void MoveCell(Direction direction, std::string dirStr, int& pos, int count, int xOffset, int yOffset);
	bool IsStuck(int xOffset, int yOffset);
private:
	Maze* maze = nullptr;
	std::vector<std::string> directions;
	int xPos;
	int yPos;
};
#pragma once
#include "Maze.h"
#include <vector>
#include <string>

struct Position
{
public:
	int X;
	int Y;
};

class Solver
{
public:
	Solver(Maze* maze);
	~Solver() = default;

public:
	void Solve();

private:
	// Helper function that checks where the walls are and if a cell has already been visited
	void MazeLoop();
	void MoveCell(Direction direction, std::string dirStr, int& pos, int count, int xOffset, int yOffset);
	bool IsStuck(int xOffset, int yOffset);
	void RemoveDirection(Direction dir);
private:
	Maze* maze = nullptr;
	std::vector<std::string> directions;
	std::vector<Position> positions;
	int xPos;
	int yPos;
};
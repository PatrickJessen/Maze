#pragma once
#include "Maze.h"
#include <vector>
#include <string>

struct Checkpoint
{
public:
	int X;
	int Y;
	int Paths;
	int Moves = 0;
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
	bool MoveToCheckpoint(int xOffset, int yOffset);
	void RemoveDirection(Direction dir);
private:
	Maze* maze = nullptr;
	std::vector<std::string> directions;
	std::vector<Checkpoint> checkpoints;
	int xPos;
	int yPos;
	// Path counter to know when to add a checkpoint
	int paths = 0;
	// If we get completely stuck this counts to 4 and then we can get spawned to the last checkpoint
	int retries = 0;
};
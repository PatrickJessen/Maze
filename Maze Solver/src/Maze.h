#pragma once
#include "Cell.h"

class Maze
{
public:
	Maze(int seed, int width, int height, int entry, int exit, Cell** cells);
	~Maze();
public:
	int GetSeed() const { return seed; }
	int GetWidth() const { return width; }
	int GetHeight() const { return height; }
	int GetEntry() const { return entry; }
	int GetExit() const { return exit; }
	Cell** GetCells() { return cells; }

private:
	int seed;
	int width;
	int height;
	int entry;
	int exit;
	Cell** cells = nullptr;
};
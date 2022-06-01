#include "Maze.h"

Maze::Maze(int seed, int width, int height, int entry, int exit, Cell** cells)
	: seed(seed), width(width), height(height), entry(entry), exit(exit), cells(cells)
{
	
}

Maze::~Maze()
{
	for (int i = 0; i < width; i++)
		delete[] cells[i];

	delete[] cells;
	cells = nullptr;
}

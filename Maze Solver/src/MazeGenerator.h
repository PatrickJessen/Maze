#pragma once
#include <fstream>
#include "Maze.h"

class MazeGenerator
{
public:
	static Maze* GenerateMazeFromFile(const char* path);

private:
	static Cell** InitCells(int width, int height);
	// Loops through each line of the 2d array and appends them to a string
	static void ConvertArrayToString(std::string& str, std::string& line, int width);
	static std::string GetValueFromString(std::string str, int& counter);
	static void ApplyValueToCells(int width, int height, std::string& str, Cell** cells);
};
#include "MazeGenerator.h"
#include <fstream>
#include <string>
#include <iostream>

static std::ifstream file;

Maze* MazeGenerator::GenerateMazeFromFile(const char* path)
{
	file = std::ifstream(path, std::ifstream::binary);

	if (file)
	{
		int seed = 0, width = 0, height = 0, entry = 0, exit = 0;
		std::string line;
		int currentLine = 0;
		while (currentLine < 3)
		{
			std::getline(file, line);
			if (currentLine == 0)
				seed = atoi(line.c_str());
			else if (currentLine == 1)
				sscanf_s(line.c_str(), "%i %i", &width, &height);
			else if (currentLine == 2)
				sscanf_s(line.c_str(), "%i %i", &entry, &exit);
			
			currentLine++;
		}

		std::getline(file, line);
		std::string temp = "";
		ConvertArrayToString(temp, line, height);

		Cell** cells = InitCells(width, height);

		ApplyValueToCells(width, height, temp, cells);

		return new Maze(seed, width, height, entry, exit, cells);
	}
	return nullptr;
}

Cell** MazeGenerator::InitCells(int width, int height)
{
	Cell** cells = nullptr;
	cells = new Cell * [height];
	for (int i = 0; i < height; i++)
		cells[i] = new Cell[width];

	return cells;
}

void MazeGenerator::ConvertArrayToString(std::string& str, std::string& line, int width)
{
	for (int i = 0; i < width; i++)
	{
		str += line;
		str += ",";
		std::getline(file, line);
	}
}

std::string MazeGenerator::GetValueFromString(std::string str, int& counter)
{
	std::string temp = "";
	for (int j = counter; j < str.size(); j++)
	{
		if (str[j] != ',')
		{
			temp += str[j];
		}
		else
		{
			counter++;
			break;
		}
		counter++;
	}
	return temp;
}

void MazeGenerator::ApplyValueToCells(int width, int height, std::string& str, Cell** cells)
{
	int counter = 0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			std::string stringVal = GetValueFromString(str, counter).c_str();
			uint8_t value = 0;

			if (stringVal != "")
			{
				value = atoi(stringVal.c_str());
				cells[i][j].AddDirection(value);
			}
		}
	}
}

#include "Solver.h"
#include <iostream>
#include <time.h>

Solver::Solver(Maze* maze)
	: maze(maze)
{
	xPos = maze->GetEntry() - 1;
	yPos = 0;
	maze->GetCells()[yPos][xPos].hasBeenVisited = true;
	srand(time(NULL));
}

void Solver::Solve()
{
	//While we havent hit the exit
	while (yPos != maze->GetHeight() - 1 || xPos != maze->GetExit() - 1)
	{
		std::vector<Direction> dirs;
		int count = 0;
		for (auto& x : maze->GetCells()[yPos][xPos].walls)
		{
			if (!x.second)
			{
				count++;
				dirs.push_back(x.first);
			}
		}
		/*if (yPos != 0 && count == 3)
			maze->GetCells()[yPos][xPos].hasBeenVisited = false;*/

		int randDir = rand() % dirs.size();
		switch (dirs[randDir])
		{
		case Direction::NORTH:
			if (yPos != 0)
				MoveCell(Direction::NORTH, "NORTH", yPos, -1, 0, -1);
			break;
		case Direction::SOUTH:
			MoveCell(Direction::SOUTH, "SOUTH", yPos, 1, 0, 1);
			break;
		case Direction::EAST:
			MoveCell(Direction::EAST, "EAST", xPos, 1, 1, 0);
			break;
		case Direction::WEST:
			MoveCell(Direction::WEST, "WEST", xPos, -1, -1, 0);
			break;
		default:
			break;
		}



		int value = maze->GetCells()[yPos][xPos].value;

	}

	for (int i = 0; i < directions.size(); i++)
	{
		std::cout << directions[i] << "\n";
	}
	std::cout << directions.size() - 1 << "\n";
}

void Solver::MoveCell(Direction direction, std::string dirStr, int& pos, int count, int xOffset, int yOffset)
{
	if (!maze->GetCells()[yPos + yOffset][xPos + xOffset].hasBeenVisited)
	{
		positions.push_back({ xPos, yPos });
		pos += count;
		maze->GetCells()[yPos][xPos].hasBeenVisited = true;
		directions.push_back(dirStr);
	}
	else if (IsStuck(xOffset, yOffset) && positions.size() > 0)
	{
		xPos = positions.back().X;
		yPos = positions.back().Y;
		maze->GetCells()[yPos][xPos].hasBeenVisited = true;
		positions.pop_back();
		//directions.push_back(directions[directions.size() - 1]);
	}
}

bool Solver::IsStuck(int xOffset, int yOffset)
{
	bool visited = maze->GetCells()[yPos][xPos].hasBeenVisited;
	bool deadEnd = maze->GetCells()[yPos][xPos].isDeadEnd;
	if (visited && deadEnd)
		return true;
	return false;
}

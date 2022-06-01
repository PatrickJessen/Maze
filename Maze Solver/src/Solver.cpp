#include "Solver.h"
#include <iostream>
#include <time.h>

Solver::Solver(Maze* maze)
	: maze(maze)
{
	xPos = maze->GetEntry() - 1;
	yPos = 0;
	srand(time(NULL));
}

void Solver::Solve()
{
	// While we havent hit the exit
	while (yPos != maze->GetHeight() - 1 || xPos != maze->GetExit() - 1)
	{
		// Random number between 0 and 3 decides where to go next in the array
		int dir = rand() % 4;
		int value = maze->GetCells()[yPos][xPos].value;

		switch (dir)
		{
		case 0:
			if (yPos != 0)
				MoveCell(Direction::NORTH, "NORTH", yPos, -1, 0, -1);
			break;
		case 1:
			MoveCell(Direction::SOUTH, "SOUTH", yPos, 1, 0, 1);
			break;
		case 2:
			MoveCell(Direction::WEST, "WEST", xPos, -1, -1, 0);
			break;
		case 3:
			MoveCell(Direction::EAST, "EAST", xPos, 1, 1, 0);
			break;
		default:
			break;
		}

	}

	for (int i = 0; i < directions.size(); i++)
	{
		std::cout << directions[i] << "\n";
	}
		std::cout << directions.size() << "\n";
}

void Solver::MoveCell(Direction direction, std::string dirStr, int& pos, int count, int xOffset, int yOffset)
{
	if (!maze->GetCells()[yPos][xPos].walls[direction] && !maze->GetCells()[yPos + yOffset][xPos + xOffset].isDeadEnd && !maze->GetCells()[yPos + yOffset][xPos + xOffset].hasBeenVisited)
	{
		maze->GetCells()[yPos][xPos].hasBeenVisited = true;
		pos += count;
		directions.push_back(dirStr);
	}
}

bool Solver::IsStuck(int xOffset, int yOffset)
{
	if (maze->GetCells()[yPos + yOffset][xPos + xOffset].hasBeenVisited && maze->GetCells()[yPos + yOffset][xPos + xOffset].isDeadEnd)
		return true;
	return false;
}

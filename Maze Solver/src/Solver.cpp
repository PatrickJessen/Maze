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
		// if there is multiple ways to go create a checkpoint to go back to, to try another way if one way was blocked
		if (count > 1)
		{
			checkpoint = { xPos, yPos };
			maze->GetCells()[yPos][xPos].hasBeenVisited = false;
		}

		if (maze->GetCells()[yPos][xPos].isDeadEnd)
		{
			xPos = checkpoint.X;
			yPos = checkpoint.Y;
		}

		for (int i = 0; i < dirs.size(); i++)
		{
			if (dirs[i] == Direction::NORTH)
			{

				if (yPos != 0)
				{
					MoveCell(Direction::NORTH, "NORTH", yPos, -1, 0, -1);
				}
			}
			else if (dirs[i] == Direction::SOUTH)
			{
				MoveCell(Direction::SOUTH, "SOUTH", yPos, 1, 0, 1);
			}
			else if (dirs[i] == Direction::EAST)
			{
				MoveCell(Direction::EAST, "EAST", xPos, 1, 1, 0);
			}
			else if (dirs[i] == Direction::WEST)
			{
				MoveCell(Direction::WEST, "WEST", xPos, -1, -1, 0);
			}
		}


		int value = maze->GetCells()[yPos][xPos].value;

		/*if (value == 4)
		{
			std::cout << maze->GetCells()[yPos][xPos].hasBeenVisited << "\n";
		}*/
		// Random number between 0 and 3 decides where to go next in the array
		//int dir = rand() % 4;
		/*switch (dir)
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
		}*/


		//for (int i = 0; i < visitedCells.size(); i++)
		//	if (maze->GetCells()[yPos][xPos] == visitedCells[i])
		//	{
		//		dir = rand() % 4;
		//		break;
		//	}
		// TODO: if i get stuck go back in the array to find another way

	}

	for (int i = 0; i < directions.size(); i++)
	{
		std::cout << directions[i] << "\n";
	}
	std::cout << directions.size() << "\n";
}

void Solver::MoveCell(Direction direction, std::string dirStr, int& pos, int count, int xOffset, int yOffset)
{
	if (!maze->GetCells()[yPos][xPos].walls[direction] && !maze->GetCells()[yPos + yOffset][xPos + xOffset].hasBeenVisited)
	{
		//visitedCells.push_back(maze->GetCells()[yPos][xPos]);
		pos += count;
		//positions.push_back({ xPos, yPos });
		//if (xPos != checkpoint.X && yPos != checkpoint.Y)
			maze->GetCells()[yPos][xPos].hasBeenVisited = true;
		directions.push_back(dirStr);
	}
}

bool Solver::IsStuck(int xOffset, int yOffset)
{
	bool visited = maze->GetCells()[yPos + yOffset][xPos + xOffset].hasBeenVisited;
	bool deadEnd = maze->GetCells()[yPos + yOffset][xPos + xOffset].isDeadEnd;
	if (maze->GetCells()[yPos + yOffset][xPos + xOffset].hasBeenVisited && maze->GetCells()[yPos + yOffset][xPos + xOffset].isDeadEnd)
		return true;
	return false;
}

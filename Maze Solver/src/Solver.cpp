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
	MazeLoop();

	for (int i = 0; i < directions.size(); i++)
	{
		std::cout << directions[i] << "\n";
	}
	std::cout << directions.size() - 1 << "\n";
}

// Recursive function that gets called each time we find a way to another cell
void Solver::MazeLoop()
{
	// if we hit the exit return.
	if (yPos == maze->GetHeight() - 1 && xPos == maze->GetExit() - 1)
		return;

	// loop through the walls at the current position
	for (auto& x : maze->GetCells()[yPos][xPos].walls)
	{
		// if there isnt a wall, move to that cell.
		if (!x.second)
		{
			maze->GetCells()[yPos][xPos].hasBeenVisited = true;
			maze->GetCells()[yPos][xPos].walls[x.first] = true;
			switch (x.first)
			{
			case Direction::NORTH:
				if (yPos != 0)
				{
					MoveCell(Direction::NORTH, "NORTH", yPos, -1, 0, -1);
				}
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
		}
	}
}

void Solver::MoveCell(Direction direction, std::string dirStr, int& pos, int count, int xOffset, int yOffset)
{
	// First check if we are stuck or our next direction is a dead end
	if (IsStuck(xOffset, yOffset))
	{
		if (positions.size() > 0)
		{
			// If we get stuck we go one position back to find another way.
			xPos = positions.back().X;
			yPos = positions.back().Y;
			positions.pop_back();
			directions.pop_back();
		}
		//maze->GetCells()[yPos][xPos].hasBeenVisited = true;
	}
	// If we are not stuck and we havent visited the next cell yet, we push back our current position to a vector so we can go back if we get stuck, Then we visit the next cell and push back the direction we whent
	else if (!maze->GetCells()[yPos + yOffset][xPos + xOffset].hasBeenVisited)
	{
		positions.push_back({ xPos, yPos });
		pos += count;
		RemoveDirection(direction);
		directions.push_back(dirStr);
	}
	MazeLoop();
}

bool Solver::IsStuck(int xOffset, int yOffset)
{
	//if (yPos + yOffset != maze->GetHeight())
	{
		bool visited = maze->GetCells()[yPos + yOffset][xPos + xOffset].hasBeenVisited;
		bool deadEnd = maze->GetCells()[yPos][xPos].isDeadEnd;
		if (deadEnd || visited && deadEnd || visited)
		{
			return true;
		}
	}
	return false;
}

void Solver::RemoveDirection(Direction dir)
{
	switch (dir)
	{
	case Direction::NORTH:
		maze->GetCells()[yPos][xPos].walls[Direction::SOUTH] = true;
		break;
	case Direction::SOUTH:
		maze->GetCells()[yPos][xPos].walls[Direction::NORTH] = true;
		break;
	case Direction::EAST:
		maze->GetCells()[yPos][xPos].walls[Direction::WEST] = true;
		break;
	case Direction::WEST:
		maze->GetCells()[yPos][xPos].walls[Direction::EAST] = true;
		break;
	default:
		break;
	}
}

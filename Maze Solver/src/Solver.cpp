#include "Solver.h"
#include <iostream>
#include <time.h>

Solver::Solver(Maze* maze)
	: maze(maze)
{
	xPos = maze->GetEntry() - 1;
	yPos = 0;
	checkpoints.push_back({ xPos, yPos });
	maze->GetCells()[yPos][xPos].visited = true;
	srand(time(NULL));
}

void Solver::Solve()
{
	while (yPos != maze->GetHeight() - 1 || xPos != maze->GetExit() - 1)
	{
		MazeLoop();
	}

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
		if (yPos == maze->GetHeight() - 1 && xPos == maze->GetExit() - 1)
			return;
		// if there isnt a wall, move to that cell.
		if (!x.second)
		{
			maze->GetCells()[yPos][xPos].visited = true;
			switch (x.first)
			{
			case Direction::NORTH:
				if (yPos != 0)
				{
					MoveCell(Direction::NORTH, "UP", yPos, -1, 0, -1);
				}
				break;
			case Direction::SOUTH:
				MoveCell(Direction::SOUTH, "DOWN", yPos, 1, 0, 1);
				break;
			case Direction::EAST:
				MoveCell(Direction::EAST, "RIGHT", xPos, 1, 1, 0);
				break;
			case Direction::WEST:
				MoveCell(Direction::WEST, "LEFT", xPos, -1, -1, 0);
				break;
			default:
				break;
			}
		}
	}
}

void Solver::MoveCell(Direction direction, std::string dirStr, int& pos, int count, int xOffset, int yOffset)
{
	// Make sure we dont go outside of the array
	if (xPos + xOffset < maze->GetWidth() && yPos + yOffset < maze->GetHeight())
	{
		paths = 0;

		// First check if we are stuck or our next direction is a dead end
		if (MoveToCheckpoint(xOffset, yOffset))
		{
			xPos = checkpoints.back().X;
			yPos = checkpoints.back().Y;
			for (int i = 0; i < checkpoints.back().Moves; i++)
				if (directions.size() > 0)
					directions.pop_back();
			/*if (checkpoints.back().Paths <= 0)
			{
				checkpoints.pop_back();
			}*/
			checkpoints.back().Paths -= 1;
			checkpoints.back().Moves = 0;
			
			return;
		}
		// If we are not stuck and we havent visited the next cell yet, we push back our current position to a vector so we can go back if we get stuck, Then we visit the next cell and push back the direction we whent
		else if (!maze->GetCells()[yPos + yOffset][xPos + xOffset].visited)
		{
			retries = 0;
			pos += count;
			directions.push_back(dirStr);
			for (auto& x : maze->GetCells()[yPos][xPos].walls)
			{
				if (!x.second)
					paths++;
			}
			if (checkpoints.size() > 0)
				checkpoints.back().Moves++;
			if (paths > 2)
			{
				checkpoints.push_back({ xPos, yPos, paths });
			}
			MazeLoop();
		}
		else
		{
			retries++;
		}
	}
}

bool Solver::IsStuck(int xOffset, int yOffset)
{
	//if (yPos + yOffset != maze->GetHeight())
	{
		//bool visited = maze->GetCells()[yPos + yOffset][xPos + xOffset].visited;
		bool deadEnd = maze->GetCells()[yPos][xPos].isDeadEnd;
		if (deadEnd)
		{
			return true;
		}
	}
	return false;
}

bool Solver::MoveToCheckpoint(int xOffset, int yOffset)
{
	if (checkpoints.size() > 0)
	{
		if (IsStuck(xOffset, yOffset))
		{
			// If we get stuck we go one position back to find another way.	

			return true;
		}
		else if (retries > 3)
		{
			checkpoints.back().Paths = 0;
			checkpoints.pop_back();
			retries = 0;
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

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
	std::cout << directions.size() << "\n";
}

void Solver::MazeLoop()
{
	for (int i = 0; i < maze->GetCells()[yPos][xPos].openDirections.size(); i++)
	{
		if (yPos == maze->GetHeight() - 1 && xPos == maze->GetExit() - 1)
			return;
		switch (maze->GetCells()[yPos][xPos].openDirections[i])
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

void Solver::MoveCell(Direction direction, std::string dirStr, int& pos, int count, int xOffset, int yOffset)
{
	// Make sure we dont go outside of the array
	if (xPos + xOffset < maze->GetWidth() && yPos + yOffset < maze->GetHeight())
	{
		// if we get stuck go to the last checkpoint in the checkpoint list
		if (IsStuck(xOffset, yOffset) || retries > 3)
		{
			if (checkpoints.size() > 0)
			{
				MoveToCheckpoint();
			}
		}
		// if we havent visited the next cell, move to the cell.
		else if (!maze->GetCells()[yPos + yOffset][xPos + xOffset].visited)
		{
			pos += count;
			maze->GetCells()[yPos][xPos].visited = true;

			// count the moves from checkpoint to a dead end
			if (checkpoints.size() > 0)
				checkpoints.back().Moves++;

			// if theres more than 2 possible directions to go, we add a checkpoint to go back to if we get stuck.
			if (maze->GetCells()[yPos][xPos].openDirections.size() > 2)
			{
				paths = maze->GetCells()[yPos][xPos].openDirections.size();
				checkpoints.push_back({ xPos, yPos, paths });
			}
			directions.push_back(dirStr);

			// remove the opposite direction we came from, so we dont have to try to go back to it again.
			RemoveDirection(direction);
			retries = 0;
			MazeLoop();
		}
		else
		{
			// if we get completely stuck, we add to retries.
			// once this hits 4 we go back to the latest checkpoint.
			retries++;
		}
	}
}

bool Solver::IsStuck(int xOffset, int yOffset)
{
	return maze->GetCells()[yPos][xPos].isDeadEnd;
}

void Solver::MoveToCheckpoint()
{
	xPos = checkpoints.back().X;
	yPos = checkpoints.back().Y;

	// Once we get stuck we loop through all the moves we counted since last checkpoint, to remove all the directions we took
	for (int i = 0; i < checkpoints.back().Moves; i++)
		if (directions.size() > 0)
			directions.pop_back();

	checkpoints.back().Paths -= 1;
	checkpoints.back().Moves = 0;

	if (checkpoints.back().Paths <= 0)
		checkpoints.pop_back();

	retries = 0;
}

void Solver::RemoveDirection(Direction dir)
{
	switch (dir)
	{
	case Direction::NORTH:
		RemoveOppositeDirection(Direction::SOUTH);
		break;
	case Direction::SOUTH:
		RemoveOppositeDirection(Direction::NORTH);
		break;
	case Direction::EAST:
		RemoveOppositeDirection(Direction::WEST);
		break;
	case Direction::WEST:
		RemoveOppositeDirection(Direction::EAST);
		break;
	default:
		break;
	}

	// if there is no direction to go to, we go back to the latest checkpoint.
	if (maze->GetCells()[yPos][xPos].openDirections.empty())
		MoveToCheckpoint();

}

void Solver::RemoveOppositeDirection(Direction dir)
{
	for (int i = 0; i < maze->GetCells()[yPos][xPos].openDirections.size(); i++)
		if (maze->GetCells()[yPos][xPos].openDirections[i] == dir)
			maze->GetCells()[yPos][xPos].openDirections.erase(maze->GetCells()[yPos][xPos].openDirections.begin() + i);
}

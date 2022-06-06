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
		// Add directions to a vector that dosent have a wall
		for (auto& x : maze->GetCells()[yPos][xPos].walls)
			if (!x.second)
				dirs.push_back(x.first);

		// Choose a random direction to go
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
	// Possible Fix: If i get stuck go one back then check for possible directions, if none go one back again and do the same


	// First check if we are stuck or our next direction is a dead end
	if (IsStuck(xOffset, yOffset))
	{
		maze->GetCells()[yPos][xPos].hasBeenVisited = false;
		if (positions.size() > 0)
		{
			// If we get stuck we go one position back to find another way.
			xPos = positions.back().X;
			yPos = positions.back().Y;
			positions.pop_back();
			directions.pop_back();
			//directions.push_back(directions.back());
		}
		maze->GetCells()[yPos][xPos].hasBeenVisited = true;
	}
	// If we are not stuck and we havent visited the next cell yet, we push back our current position to a vector so we can go back if we get stuck, Then we visit the next cell and push back the direction we whent
	else if (!maze->GetCells()[yPos + yOffset][xPos + xOffset].hasBeenVisited)
	{
		positions.push_back({ xPos, yPos });
		maze->GetCells()[yPos][xPos].hasBeenVisited = true;
		pos += count;
		RemoveDirection(direction);
		maze->GetCells()[yPos][xPos].hasBeenVisited = true;
		directions.push_back(dirStr);
	}
}

bool Solver::IsStuck(int xOffset, int yOffset)
{
	bool visited = maze->GetCells()[yPos + yOffset][xPos + xOffset].hasBeenVisited;
	bool deadEnd = maze->GetCells()[yPos][xPos].isDeadEnd;
	if (deadEnd || visited && deadEnd)
	{
		return true;
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

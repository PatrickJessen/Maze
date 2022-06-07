#include <iostream>
#include <string>
#include <string>
#include "MazeGenerator.h"
#include "Solver.h"

int main()
{

	// Works with 3x3 and 5x5 maze, but with other mazes it traps itself in a corner
	Maze* maze = MazeGenerator::GenerateMazeFromFile("assets/mazes/5x5_32736.dat");
	
	/*for (int i = 0; i < maze->GetWidth(); i++)
	{
		for (int j = 0; j < maze->GetHeight(); j++)
		{
			int value = maze->GetCells()[i][j].value;
			std::cout << value << ",";
		}
		std::cout << "\n";
	}*/

	Solver solve(maze);
	solve.Solve();

	delete maze;

	return 0;
}
#include <iostream>
#include <string>
#include <string>
#include "MazeGenerator.h"
#include "Solver.h"

int main()
{

	// Works with 3x3 and 5x5 maze, but with other mazes it traps itself in a corner
	Maze* maze = MazeGenerator::GenerateMazeFromFile("assets/mazes/400x566_11860.dat");

	
	//for (int i = 0; i < maze->GetHeight(); i++)
	//{
	//	for (int j = 0; j < maze->GetWidth(); j++)
	//	{
	//		int value = maze->GetCells()[i][j].value;
	//		std::cout << value << ",";
	//	}
	//	std::cout << "\n";
	//}

	Solver solve(maze);
	solve.Solve();

	delete maze;

	return 0;
}
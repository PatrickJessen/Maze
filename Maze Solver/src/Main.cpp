#include <iostream>
#include <string>
#include <string>
#include "MazeGenerator.h"
#include "Solver.h"
#include <map>

int main()
{
	std::map<int, std::string> mazes;
	mazes.emplace(1, "assets/mazes/3x3_1.dat");
	mazes.emplace(32736, "assets/mazes/5x5_32736.dat");
	mazes.emplace(2936, "assets/mazes/10x10_2936.dat");
	mazes.emplace(19172, "assets/mazes/15x15_19172.dat");
	mazes.emplace(5406, "assets/mazes/20x28_5406.dat");
	mazes.emplace(2412, "assets/mazes/24x34_2412.dat");
	mazes.emplace(16793, "assets/mazes/42x60_16793.dat");
	mazes.emplace(1952, "assets/mazes/50x75_1952.dat");
	mazes.emplace(11860, "assets/mazes/400x566_11860.dat");
	mazes.emplace(25534, "assets/mazes/1000x1000_25534.dat");


	Maze* maze = MazeGenerator::GenerateMazeFromFile(mazes[1952].c_str());

	
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
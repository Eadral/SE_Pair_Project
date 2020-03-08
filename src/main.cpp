#include <iostream>
#include <fstream>

#include "solver.hpp"

using namespace std;

int main(int argc, char **argv)
{
	// TODO(zyc): better args handling
	char* input_filename = argv[2];
	char* output_filename = argv[4];
	
	ifstream fin(input_filename);
	ofstream fout(output_filename);

	Solver solver(fin, fout);
	int err = solver.Solve();
	if (err) return err;

	return 0;
}


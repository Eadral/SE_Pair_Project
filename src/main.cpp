#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char **argv)
{
	// TODO(zyc): better args handling
	char* input_filename = argv[2];
	char* output_filename = argv[4];
	
	ifstream fin(input_filename);
	ofstream fout(output_filename);

	string test;

	fin >> test;
	fout << test;
    
	return 0;
}


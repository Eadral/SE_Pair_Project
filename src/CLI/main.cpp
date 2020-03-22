// Copyright 2020 Yucong Zhu
#include <iostream>
#include <fstream>

#include "../../src/Core/solver.h"

int main(int argc, char* argv[]) {
    std::ios_base::sync_with_stdio(false);
    
    if (argv == nullptr)
        return -1;
    
    std::string input_filename;
    std::string output_filename;
    for (int i = 0; i < argc-1; i++) {
        if (strcmp(argv[i], "-i") == 0)
            input_filename = std::string(argv[i + 1]);
        if (strcmp(argv[i], "-o") == 0)
            output_filename = std::string(argv[i + 1]);
    }
    if (input_filename.empty() || output_filename.empty()) {
        std::cout << "Usage: intersect.exe -i input.txt -o output.txt" << std::endl;
        return -1;
    }
    
    std::ifstream fin(input_filename);
    std::ofstream fout(output_filename);
    if (!fin.is_open()) {
        exit(-9);
    }
    
    Solver solver(fin, fout);
    const auto err = solver.Solve();
    if (err) {
        std::cerr << ErrorString(err) << endl;
        exit(err);
    }
    // AddLine(0, 0, 1, 1);
    // AddLine(1, 0, 0, 1);
    // int ans = GetIntersectionsSize();
    // printf("%d\n", ans);
    // RemoveLine(1, 0, 0, 1);
    // ans = GetIntersectionsSize();
    // printf("%d\n", ans);
    //
    return 0;
}


// Copyright 2020 Yucong Zhu
#include <iostream>
#include <fstream>

#include "solver.hpp"


int main(int argc, char *argv[]) {
    if (argv == nullptr)
        return -1;
    // TODO(zyc): better args handling
    const char* input_filename = argv[2];
    const char* output_filename = argv[4];

    std::ifstream fin(input_filename);
    std::ofstream fout(output_filename);

    Solver solver(fin, fout);
    const auto err = solver.Solve();
    if (err) return err;

    return 0;
}


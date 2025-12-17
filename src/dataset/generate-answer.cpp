/**
 * @file src/dataset/generate-answer.cpp
 * @brief Generate best algorithm to validate AI accuracy.
 */

#include "label.hpp"
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char ** argv) {
    if (argc != 4) {
        std::cerr << "Usage: generate-answer /path/to/source/file "
                     "/path/to/output/file direction\n";
        return -1;
    }

    std::ifstream fin(argv[1]);
    std::ofstream fout(argv[2]);
    const int direction = std::stoi(argv[3]);
    if (fin.fail() || fout.fail()) {
        std::cerr << "Failed to open file\n";
        return -1;
    }

    smart_sort::Array source;
    while (fin) {
        smart_sort::getRawData(source, fin);
        if (fin) {
            const int best_algorithm =
                smart_sort::getBestAlgorithm(source, direction);
            fout << best_algorithm << "\n";
            fout.flush();
        }
    }

    return 0;
}

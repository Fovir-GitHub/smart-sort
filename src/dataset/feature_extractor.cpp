#include "label.hpp"
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char ** argv) {
    if (argc != 3) {
        std::cerr << "Usage: feature_extractor /path/to/source/file "
                     "/path/to/output/file\n";
        return -1;
    }

    std::ifstream fin(argv[1]);
    std::ofstream fout(argv[2]);
    if (fin.fail() || fout.fail()) {
        std::cerr << "Failed to open file\n";
        return -1;
    }

    int line = 1;
    int total_lines = 0;
    std::string temp;
    while (std::getline(fin, temp)) {
        total_lines++;
    }
    fin.clear();
    fin.seekg(0);

    smart_sort::Array source;
    while (fin) {
        smart_sort::getRawData(source, fin);
        if (fin) {
            smart_sort::labelData(source, fout);
            std::cout << "Current Line: " << line++ << " / " << total_lines
                      << "\n";
        }
    }

    return 0;
}

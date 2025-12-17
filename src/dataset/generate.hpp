#pragma once
    #include <algorithm>
    #include <cstdlib>
    #include <ctime>
    #include <fstream>
    #include <iostream>
    #include <string>
    #include <vector>
namespace smart_sort {
    void fillRandom(std::vector<int> & arr, int maxValue);
    void printArray(const std::vector<int> & arr);
    enum class DataType {
    Random = 0,
    NearlySorted,
    Reversed,
    FewUnique,
    LargeRandom,
};
std::string dataTypeToString(DataType t);
void generateRandom(std::vector<int> & arr);
void generateNearlySorted_increasing(std::vector<int> & arr);
void generateNearlySorted_decreasing(std::vector<int> & arr);
void generateReversed(std::vector<int> & arr);
void generateFewUnique(std::vector<int> & arr);
void generateLargeRandom(std::vector<int> & arr);
void generateByType(std::vector<int> & arr, DataType type);
int generateSizeForType(DataType type);
}

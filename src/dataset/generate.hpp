#pragma once

#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

namespace smart_sort {

enum class DataType : std::uint8_t {
    Random = 0,
    NearlySorted,
    Reversed,
    FewUnique,
    LargeRandom,
};

void fillRandom(std::vector<int> & arr, int maxValue);

void printArray(const std::vector<int> & arr);

std::string dataTypeToString(DataType t);

void generateRandom(std::vector<int> & arr);

void generateNearlySortedAscending(std::vector<int> & arr);

void generateNearlySortedDescending(std::vector<int> & arr);

void generateReversed(std::vector<int> & arr);

void generateFewUnique(std::vector<int> & arr);

void generateLargeRandom(std::vector<int> & arr);

void generateByType(std::vector<int> & arr, DataType type);

int generateSizeForType(DataType type);

} // namespace smart_sort

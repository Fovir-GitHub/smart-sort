#pragma once

#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

namespace smart_sort {

enum class DATASET_CONSTANT : int {
    DEFAULT_RANDOM_LOWER_SIZE = 10,
    DEFAULT_RANDOM_UPPER_SIZE = 5000,
    DEFAULT_SAMPLE_SIZE = 10000,
    FEW_UNIQUE = 5,
    LARGE_RANDOM_LOWER_SIZE = 20000,
    LARGE_RANDOM_UPPER_SIZE = 100000,
    NUMBER_OF_DATA_TYPE = 5,
    SMALL_ARRAY_SIZE = 1000,
    SWAP_ELEMENT_RATIO = 100,
    VALUE_UPPER_BOUNDARY = 1000000,
};

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

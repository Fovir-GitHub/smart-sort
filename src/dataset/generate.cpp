#include "generate.hpp"
#include "core/utils.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <vector>

static int randomInteger(int upper, int lower = 0) {
    static std::mt19937 gen = smart_sort::getRandomGenerator();
    std::uniform_int_distribution<> dist(lower, std::max(lower, upper - 1));
    return dist(gen);
}

namespace smart_sort {

// Method: Generate Random Array
void fillRandom(std::vector<int> & arr, int maxValue) {
    std::generate(arr.begin(), arr.end(),
                  [maxValue]() { return randomInteger(maxValue); });
}

// printArray
void printArray(const std::vector<int> & arr) {
    for (const int & i : arr) {
        std::cout << i << " ";
    }
    std::cout << "\n";
}

std::string dataTypeToString(DataType t) {
    switch (t) {
    case DataType::Random:
        return "Random";
    case DataType::NearlySorted:
        return "NearlySorted";
    case DataType::Reversed:
        return "Reversed";
    case DataType::FewUnique:
        return "FewUnique";
    case DataType::LargeRandom:
        return "LargeRandom";
    default:
        return "Unknown";
    }
}

// Five methods to generate different types of raw data

// 1. Random(Normal size)
void generateRandom(std::vector<int> & arr) {
    fillRandom(arr, static_cast<int>(DATASET_CONSTANT::VALUE_UPPER_BOUNDARY));
}

static void swapElements(std::vector<int> & arr) {
    const int n = static_cast<int>(arr.size());
    const int swaps =
        std::max(1, n / static_cast<int>(DATASET_CONSTANT::SWAP_ELEMENT_RATIO));
    for (int k = 0; k < swaps; ++k) {
        const int i = randomInteger(n);
        const int j = randomInteger(n);
        std::swap(arr[i], arr[j]);
    }
}

/*
 2. Nearly Sorted(The logic is: generate the increasing array / decreasing
 array, and then change 1% of them)
 */
void generateNearlySortedAscending(std::vector<int> & arr) {
    std::iota(arr.begin(), arr.end(), 0);
    swapElements(arr);
}

void generateNearlySortedDescending(std::vector<int> & arr) {
    std::iota(arr.rbegin(), arr.rend(), 0);
    swapElements(arr);
}

// 3. Reversed
void generateReversed(std::vector<int> & arr) {
    std::iota(arr.rbegin(), arr.rend(), 1);
}

/*
4. FewUnique(The logic is: generate the array with limited numbers but very big
size, so that the array has many elements repeated)
*/
void generateFewUnique(std::vector<int> & arr) {
    std::generate(arr.begin(), arr.end(), []() {
        return randomInteger(static_cast<int>(DATASET_CONSTANT::FEW_UNIQUE));
    });
}

// 5. LargeRandom：has very big array size
void generateLargeRandom(std::vector<int> & arr) {
    fillRandom(arr, static_cast<int>(DATASET_CONSTANT::VALUE_UPPER_BOUNDARY));
}

// use the 5 methods according to the type needed
void generateByType(std::vector<int> & arr, DataType type) {
    switch (type) {
    case DataType::Random:
        generateRandom(arr);
        break;
    case DataType::NearlySorted: {
        const int coin = randomInteger(2);
        if (coin == 0) {
            generateNearlySortedDescending(arr);
        } else {
            generateNearlySortedAscending(arr);
        }
        break;
    }
    case DataType::Reversed:
        generateReversed(arr);
        break;
    case DataType::FewUnique:
        generateFewUnique(arr);
        break;
    case DataType::LargeRandom:
        generateLargeRandom(arr);
        break;
    }
}

/*
Decide the size of the array according to whether it is large random:
Normal Random: 10 ~ 5000
Large Random: 20000 ~ 100000
*/
int generateSizeForType(DataType type) {
    switch (type) {
    case DataType::LargeRandom: {
        return randomInteger(
            static_cast<int>(DATASET_CONSTANT::LARGE_RANDOM_UPPER_SIZE),
            static_cast<int>(DATASET_CONSTANT::LARGE_RANDOM_LOWER_SIZE));
    }
    default: {
        return randomInteger(
            static_cast<int>(DATASET_CONSTANT::DEFAULT_RANDOM_UPPER_SIZE),
            static_cast<int>(DATASET_CONSTANT::DEFAULT_RANDOM_LOWER_SIZE));
    }
    }
}

} // namespace smart_sort

int main(int argc, char ** argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " /path/to/output/file\n";
        return -1;
    }

    const std::string filepath = argv[1];
    std::ofstream fout(filepath);
    if (!fout.is_open()) {
        std::cerr << "Failed to open " << filepath << " for writing.\n";
        return -1;
    } // Error

    const int samplesPerType = static_cast<int>(
        smart_sort::DATASET_CONSTANT::DEFAULT_SAMPLE_SIZE); // every type of
                                                            // data, we generate
                                                            // 20,000 samples
    int sampleId = 0;
    for (int t = 0; t < static_cast<int>(
                            smart_sort::DATASET_CONSTANT::NUMBER_OF_DATA_TYPE);
         ++t) {
        auto type = static_cast<smart_sort::DataType>(t);
        for (int k = 0; k < samplesPerType; ++k) {
            // large size or normal size
            const int n = smart_sort::generateSizeForType(type);
            std::vector<int> arr(n);

            // generate data
            smart_sort::generateByType(arr, type);

            // edit CSV
            for (const auto & data : arr) {
                fout << data << " ";
            }
            fout << "\n";
            sampleId++;
        }

        // for (int k = 0; k < samples; ++k) {
        //     // large size or normal size
        //     int n = (smart_sort::generateSizeForType(type) %
        //              static_cast<int>(smart_sort::DATASET_CONSTANT::SMALL_ARRAY_SIZE))
        //              +
        //             1;
        //     if (type == smart_sort::DataType::LargeRandom) {
        //         n = generateSizeForType(type);
        //     }
        //
        //     std::vector<int> arr(n);
        //
        //     // generate data
        //     smart_sort::generateByType(arr, type);
        //
        //     // edit CSV
        //     for (int idx = 0; idx < n; ++idx) {
        //         fout << arr[idx] << " "; // value
        //     }
        //     sampleId++;
        //     fout << "\n";
        // }
    }

    fout.close();
    std::cout << "Data written to " << filepath << "\n";
    return 0;
}

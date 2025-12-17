#include "generate.hpp"
#include "core/utils.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>

static int randomInteger(int upper, int lower = 0) {
    static std::mt19937 gen = smart_sort::getRandomGenerator();
    std::uniform_int_distribution<> dist(lower, std::max(lower, upper - 1));
    return dist(gen);
}

namespace smart_sort {

// Method: Generate Random Array
void fillRandom(std::vector<int> & arr, int maxValue) {
    for (int & i : arr) {
        i = randomInteger(maxValue);
    }
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
void generateRandom(std::vector<int> & arr) { fillRandom(arr, 1000000); }

/*
 2. Nearly Sorted(The logic is: generate the increasing array/ decreasing array,
 and then change 1% of them)
 */
void generateNearlySorted_increasing(std::vector<int> & arr) {
    int n = static_cast<int>(arr.size());

    // increasing array
    for (int i = 0; i < n; ++i) {
        arr[i] = i;
    }

    // change elements
    int swaps = std::max(1, n / 100);
    for (int k = 0; k < swaps; ++k) {
        int i = randomInteger(n);
        int j = randomInteger(n);
        std::swap(arr[i], arr[j]);
    }
}

void generateNearlySorted_decreasing(std::vector<int> & arr) {
    int n = static_cast<int>(arr.size());

    // decreasing
    for (int i = 0; i < n; ++i) {
        arr[i] = n - i;
    }

    // change
    int swaps = std::max(1, n / 100);
    for (int k = 0; k < swaps; ++k) {
        int i = randomInteger(n);
        int j = randomInteger(n);
        std::swap(arr[i], arr[j]);
    }
}

// 3. Reversed
void generateReversed(std::vector<int> & arr) {
    int n = static_cast<int>(arr.size());
    for (int i = 0; i < n; ++i) {
        arr[i] = n - i; // n, n-1, ..., 1
    }
}

/*
4. FewUnique(The logic is: generate the array with limited numbers but very big
size, so that the array has many elements repeated)
*/
void generateFewUnique(std::vector<int> & arr) {
    int nUnique = 5; // Only 5 values of the elements
    for (int & i : arr) {
        i = randomInteger(nUnique);
    }
}

// 5. LargeRandom：has very big array size
void generateLargeRandom(std::vector<int> & arr) { fillRandom(arr, 1000000); }

// use the 5 methods according to the type needed
void generateByType(std::vector<int> & arr, DataType type) {
    switch (type) {
    case DataType::Random:
        generateRandom(arr);
        break;
    case DataType::NearlySorted: {
        int coin = randomInteger(2);
        if (coin == 0) {
            generateNearlySorted_decreasing(arr);
        } else {
            generateNearlySorted_increasing(arr);
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
        int minN = 20000;
        int span = 80001; // 20000 ~ 100000
        return randomInteger(span, minN);
    }
    default: {
        int minN = 10;
        int span = 4991; // 10 ~ 5000
        return randomInteger(span, minN);
    }
    }
}

} // namespace smart_sort

int main() {
    std::ofstream fout("temp.csv");
    if (!fout.is_open()) {
        std::cerr << "Failed to open raw_data.csv for writing.\n";
        return 1;
    } // Error

    int samplesPerType =
        10000; // every type of data, we generate 20,000 samples
    int sampleId = 0;
    for (int t = 0; t < 5; ++t) {
        auto type = static_cast<smart_sort::DataType>(t);
        int samples = 0;
        switch (type) {
        case smart_sort::DataType::Random:
        case smart_sort::DataType::LargeRandom:
            samples = 30;
            break;
        case smart_sort::DataType::Reversed:
            samples = 20;
            break;
        case smart_sort::DataType::FewUnique:
        case smart_sort::DataType::NearlySorted:
            samples = 10;
            break;
        }

        samples *= 5;
        for (int k = 0; k < samples; ++k) {
            // large size or normal size
            int n = smart_sort::generateSizeForType(type);
            std::vector<int> arr(n);

            // generate data
            smart_sort::generateByType(arr, type);

            // edit CSV
            for (int idx = 0; idx < n; ++idx) {
                fout << arr[idx] << " "; // value
            }
            sampleId++;
            fout << "\n";
        }

        for (int k = 0; k < samples; ++k) {
            // large size or normal size
            int n = (smart_sort::generateSizeForType(type) % 1000) + 1;
            if (type == smart_sort::DataType::LargeRandom) {
                n = generateSizeForType(type);
            }

            std::vector<int> arr(n);

            // generate data
            smart_sort::generateByType(arr, type);

            // edit CSV
            for (int idx = 0; idx < n; ++idx) {
                fout << arr[idx] << " "; // value
            }
            sampleId++;
            fout << "\n";
        }
    }

    fout.close();
    std::cout << "Raw data written to raw_data.csv\n";
    return 0;
}

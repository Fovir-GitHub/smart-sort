#include "frontend.hpp"
#include "dataset/generate.hpp"
#include "utils.hpp"
#include <cstdlib>
#include <functional>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

namespace smart_sort {

void displayDatasetMenu() {
    const int MENU_BORDER_DEFAULT_LENGTH = 20;
    const auto PRINT_BORDER = [MENU_BORDER_DEFAULT_LENGTH](char ch) {
        std::cout << std::string(MENU_BORDER_DEFAULT_LENGTH, ch) << "\n";
    };

    PRINT_BORDER('=');
    std::cout << "Dataset Types\n";
    PRINT_BORDER('-');
    for (int i = 0; i < static_cast<int>(
                            smart_sort::DATASET_CONSTANT::NUMBER_OF_DATA_TYPE);
         i++) {
        std::cout << "[" << i + 1 << "] "
                  << smart_sort::dataTypeToString(
                         static_cast<smart_sort::DataType>(i))
                  << "\n";
    }
    PRINT_BORDER('=');
}

DataType getDatasetType() {
    int choice = 0;
    while (choice <= 0 ||
           choice > static_cast<int>(DATASET_CONSTANT::NUMBER_OF_DATA_TYPE)) {
        displayDatasetMenu();
        std::cout << "\nSelect a dataset type: ";
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
    }

    return static_cast<DataType>(choice - 1);
}

int getDatasetSize() {
    int size = 0;
    std::cout << "Enter the dataset size: ";
    std::cin >> size;
    if (std::cin.fail()) {
        std::cerr << "Failed to read an integer. Size changes to 0\n";
        size = 0;
    }

    return size;
}

std::vector<AlgorithmPerformance>
getAllAlgorithmPerformance(std::vector<int> & arr) {
    std::vector<AlgorithmPerformance> result;
    int counter = 0;
    long long execution_time = 0;
    auto cmp = [&counter](int a, int b) {
        counter++;
        return std::less<>{}(a, b);
    };
    auto algorithm_map = getAlgorithmMapByType<int>(cmp);

    for (const auto & [name, func] : algorithm_map) {
        execution_time = measureTime([arr, func]() mutable { func(arr); });
        result.emplace_back(name, counter, execution_time);
        counter = 0;
    }

    return result;
}

} // namespace smart_sort

#include "frontend.hpp"
#include "dataset/generate.hpp"
#include "utils.hpp"
#include <algorithm>
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
        execution_time = static_cast<long long>(
            measureAverageTime([arr, func]() mutable { func(arr); }));
        result.emplace_back(name, counter, execution_time);
        counter = 0;
    }

    return result;
}

void displayAlgorithmPerformanceInTable(
    const std::vector<AlgorithmPerformance> & algorithm_performance) {
    auto GET_COLUMN_WIDTH = [&](auto getter, const std::string & header) {
        if (algorithm_performance.empty()) {
            return header.length();
        }
        auto get_width = [](const auto & val) {
            if constexpr (std::is_convertible_v<decltype(val), std::string>) {
                return val.length();
            } else {
                return std::to_string(val).length();
            }
        };
        size_t max_width = 0;
        for (const auto & item : algorithm_performance) {
            max_width = std::max(max_width, get_width(getter(item)));
        }
        return std::max(max_width, header.length());
    };

    const std::string NAME_COLUMN_HEADER = "Algorithm";
    const std::string COMPARISONS_COLUMN_HEADER = "Comparison Times";
    const std::string EXECTION_TIME_COLUMN_HEADER =
        "Average Execution Time (ns)";
    const size_t NAME_COLUMN_WIDTH = GET_COLUMN_WIDTH(
        [](const auto & a) { return a.name; }, NAME_COLUMN_HEADER);
    const size_t COMPARISONS_COLUMN_WIDTH =
        GET_COLUMN_WIDTH([](const auto & a) { return a.comparisons; },
                         COMPARISONS_COLUMN_HEADER);
    const size_t EXECUTION_TIME_COLUMN_WIDTH =
        GET_COLUMN_WIDTH([](const auto & a) { return a.execution_time; },
                         EXECTION_TIME_COLUMN_HEADER);
    const auto PRINT_HORIZONTAL_LINE = [&]() {
        const static auto HORIZONTAL_COLUMN_LINE = [](const size_t length) {
            return "+" + std::string(length, '-');
        };
        std::cout << HORIZONTAL_COLUMN_LINE(NAME_COLUMN_WIDTH)
                  << HORIZONTAL_COLUMN_LINE(COMPARISONS_COLUMN_WIDTH)
                  << HORIZONTAL_COLUMN_LINE(EXECUTION_TIME_COLUMN_WIDTH)
                  << "+\n";
    };
    const auto FILL_BLANK = [](const size_t width, const std::string & s) {
        return std::string(std::max(0, static_cast<int>(width - s.length())),
                           ' ');
    };

    PRINT_HORIZONTAL_LINE();
    std::cout << "|" << NAME_COLUMN_HEADER
              << FILL_BLANK(NAME_COLUMN_WIDTH, NAME_COLUMN_HEADER) << "|"
              << COMPARISONS_COLUMN_HEADER
              << FILL_BLANK(COMPARISONS_COLUMN_WIDTH, COMPARISONS_COLUMN_HEADER)
              << "|" << EXECTION_TIME_COLUMN_HEADER
              << FILL_BLANK(EXECUTION_TIME_COLUMN_WIDTH,
                            EXECTION_TIME_COLUMN_HEADER)
              << "|\n";
    PRINT_HORIZONTAL_LINE();
    for (const auto & algo : algorithm_performance) {
        std::cout << "|" << algo.name
                  << FILL_BLANK(NAME_COLUMN_WIDTH, algo.name) << "|"
                  << FILL_BLANK(COMPARISONS_COLUMN_WIDTH,
                                std::to_string(algo.comparisons))
                  << algo.comparisons << "|"
                  << FILL_BLANK(EXECUTION_TIME_COLUMN_WIDTH,
                                std::to_string(algo.execution_time))
                  << algo.execution_time << "|\n";
        PRINT_HORIZONTAL_LINE();
    }
}

} // namespace smart_sort

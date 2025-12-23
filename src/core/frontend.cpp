#include "frontend.hpp"
#include "dataset/generate.hpp"
#include "utils.hpp"
#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

namespace smart_sort {

/**
 * @brief Display the menu of selecting dataset type.
 */
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

/**
 * @brief Get choice of dataset type from user input.
 *
 * @return The corresponding dataset type stated in the `enum
 * smart_sort::DataType`.
 */
DataType getDatasetType() {
    int choice = 0;
    // Ask for choice until entering a valid option.
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

/**
 * @brief Get the size of dataset from user input.
 *
 * @return The size of dataset. If the `size` is invalid, it will be set to
 * `0` by default.
 */
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

/**
 * @brief Get performances of all algorithms.
 *
 * @param arr An array to be sorted.
 * @param direction Determine whether the sorting direction is ascending or
 * descending.
 * @return A list of `AlgorithmPerformance`. When `arr.size()` is large, it will
 * only return results of merge sort and quick sort.
 */
std::vector<AlgorithmPerformance>
getAllAlgorithmPerformance(std::vector<int> & arr, int direction) {
    std::vector<AlgorithmPerformance> result;
    int counter = 0; // Comparison time.
    long long execution_time = 0;
    auto cmp = [&counter, direction](int a, int b) {
        counter++;
        return direction == 1 ? std::less<>{}(a, b) : std::greater<>{}(a, b);
    };
    auto algorithm_map = getAlgorithmMapByType<int>(cmp);

    for (const auto & [name, func] : algorithm_map) {
        // Skip bubble sort and insertion sort when the dataset is large scale.
        if (arr.size() >
                static_cast<size_t>(DATASET_CONSTANT::SMALL_ARRAY_SIZE) &&
            (name == "Bubble Sort" || name == "Insertion Sort")) {
            continue;
        }
        execution_time = static_cast<long long>(
            measureAverageTime([arr, func]() mutable { func(arr); }));
        result.emplace_back(name, counter, execution_time);
        counter = 0;
    }

    return result;
}

/**
 * @brief Show the results of algorithm performances in table format.
 *
 * @param algorithm_performance_ascending Algorithm performances in ascending
 * order.
 * @param algorithm_performance_descending Algorithm performances in descending
 * order.
 */
void displayAlgorithmPerformanceInTable(
    const std::vector<AlgorithmPerformance> & algorithm_performance_ascending,
    const std::vector<AlgorithmPerformance> &
        algorithm_performance_descending) {
    // Function used to get the column width.
    auto GET_COLUMN_WIDTH = [&](auto getter, const std::string & header) {
        if (algorithm_performance_ascending.empty()) {
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
        for (const auto & item : algorithm_performance_ascending) {
            max_width = std::max(max_width, get_width(getter(item)));
        }
        return std::max(max_width, header.length());
    };

    // Define column headers and use the maximum width of the column as the
    // column width.
    const std::string NAME_COLUMN_HEADER = "Algorithm";
    const std::string SORT_ASCENDING_HEADER = "Sort in Ascending Order";
    const std::string SORT_DESCENDING_HEADER = "Sort in Descending Order";

    const std::string COMPARISONS_COLUMN_HEADER_ASCENDING = "Comparison Times";
    const std::string EXECUTION_TIME_COLUMN_HEADER_ASCENDING =
        "Average Execution Time (ns)";
    const size_t NAME_COLUMN_WIDTH = GET_COLUMN_WIDTH(
        [](const auto & a) { return a.name; }, NAME_COLUMN_HEADER);
    const size_t COMPARISONS_COLUMN_ASCENDING_WIDTH =
        GET_COLUMN_WIDTH([](const auto & a) { return a.comparisons; },
                         COMPARISONS_COLUMN_HEADER_ASCENDING);
    const size_t EXECUTION_TIME_COLUMN_ASCENDING_WIDTH =
        GET_COLUMN_WIDTH([](const auto & a) { return a.execution_time; },
                         EXECUTION_TIME_COLUMN_HEADER_ASCENDING);

    const std::string COMPARISONS_COLUMN_HEADER_DESCENDING = "Comparison Times";
    const std::string EXECUTION_TIME_COLUMN_HEADER_DESCENDING =
        "Average Execution Time (ns)";
    const size_t COMPARISONS_COLUMN_DESCENDING_WIDTH =
        GET_COLUMN_WIDTH([](const auto & a) { return a.comparisons; },
                         COMPARISONS_COLUMN_HEADER_DESCENDING);
    const size_t EXECUTION_TIME_COLUMN_DESCENDING_WIDTH =
        GET_COLUMN_WIDTH([](const auto & a) { return a.execution_time; },
                         EXECUTION_TIME_COLUMN_HEADER_DESCENDING);
    const size_t SORT_ASCENDING_HEADER_WIDTH =
        COMPARISONS_COLUMN_ASCENDING_WIDTH +
        EXECUTION_TIME_COLUMN_ASCENDING_WIDTH + 1;
    const size_t SORT_DESCENDING_HEADER_WIDTH =
        COMPARISONS_COLUMN_DESCENDING_WIDTH +
        EXECUTION_TIME_COLUMN_DESCENDING_WIDTH + 1;

    const static auto HORIZONTAL_COLUMN_LINE = [](const size_t length) {
        return "+" + std::string(length, '-');
    };

    // Function used to print the border of the table.
    const auto PRINT_HORIZONTAL_LINE = [&]() {
        std::cout
            << HORIZONTAL_COLUMN_LINE(NAME_COLUMN_WIDTH)
            << HORIZONTAL_COLUMN_LINE(COMPARISONS_COLUMN_ASCENDING_WIDTH)
            << HORIZONTAL_COLUMN_LINE(EXECUTION_TIME_COLUMN_ASCENDING_WIDTH)
            << HORIZONTAL_COLUMN_LINE(COMPARISONS_COLUMN_DESCENDING_WIDTH)
            << HORIZONTAL_COLUMN_LINE(EXECUTION_TIME_COLUMN_DESCENDING_WIDTH)
            << "+\n";
    };

    // Fill blanks in each table cell.
    const auto FILL_BLANK = [](const size_t width, const std::string & s) {
        return std::string(std::max(0, static_cast<int>(width - s.length())),
                           ' ');
    };

    // Output the table.
    PRINT_HORIZONTAL_LINE();
    std::cout << "|" << std::string(NAME_COLUMN_HEADER.length(), ' ')
              << FILL_BLANK(NAME_COLUMN_WIDTH, NAME_COLUMN_HEADER) << "|"
              << SORT_ASCENDING_HEADER
              << FILL_BLANK(SORT_ASCENDING_HEADER_WIDTH, SORT_ASCENDING_HEADER)
              << "|" << SORT_DESCENDING_HEADER
              << FILL_BLANK(SORT_DESCENDING_HEADER_WIDTH,
                            SORT_DESCENDING_HEADER)
              << "|\n";
    PRINT_HORIZONTAL_LINE();
    std::cout << "|" << NAME_COLUMN_HEADER
              << FILL_BLANK(NAME_COLUMN_WIDTH, NAME_COLUMN_HEADER) << "|"
              << COMPARISONS_COLUMN_HEADER_ASCENDING
              << FILL_BLANK(COMPARISONS_COLUMN_ASCENDING_WIDTH,
                            COMPARISONS_COLUMN_HEADER_ASCENDING)
              << "|" << EXECUTION_TIME_COLUMN_HEADER_ASCENDING
              << FILL_BLANK(EXECUTION_TIME_COLUMN_ASCENDING_WIDTH,
                            EXECUTION_TIME_COLUMN_HEADER_ASCENDING)
              << "|" << COMPARISONS_COLUMN_HEADER_DESCENDING
              << FILL_BLANK(COMPARISONS_COLUMN_DESCENDING_WIDTH,
                            COMPARISONS_COLUMN_HEADER_DESCENDING)
              << "|" << EXECUTION_TIME_COLUMN_HEADER_DESCENDING
              << FILL_BLANK(EXECUTION_TIME_COLUMN_DESCENDING_WIDTH,
                            EXECUTION_TIME_COLUMN_HEADER_DESCENDING)
              << "|\n";
    PRINT_HORIZONTAL_LINE();
    for (int i = 0; i < algorithm_performance_ascending.size(); i++) {
        std::cout
            << "|" << algorithm_performance_ascending[i].name
            << FILL_BLANK(NAME_COLUMN_WIDTH,
                          algorithm_performance_ascending[i].name)
            << "|"
            << FILL_BLANK(COMPARISONS_COLUMN_ASCENDING_WIDTH,
                          std::to_string(
                              algorithm_performance_ascending[i].comparisons))
            << algorithm_performance_ascending[i].comparisons << "|"
            << FILL_BLANK(
                   EXECUTION_TIME_COLUMN_ASCENDING_WIDTH,
                   std::to_string(
                       algorithm_performance_ascending[i].execution_time))
            << algorithm_performance_ascending[i].execution_time << "|"
            << FILL_BLANK(COMPARISONS_COLUMN_ASCENDING_WIDTH,
                          std::to_string(
                              algorithm_performance_descending[i].comparisons))
            << algorithm_performance_descending[i].comparisons << "|"
            << FILL_BLANK(
                   EXECUTION_TIME_COLUMN_ASCENDING_WIDTH,
                   std::to_string(
                       algorithm_performance_descending[i].execution_time))
            << algorithm_performance_descending[i].execution_time << "|\n";
        PRINT_HORIZONTAL_LINE();
    }
    std::cout << "\n";
}

} // namespace smart_sort

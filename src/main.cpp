/**
 * @file src/main.cpp
 * @brief Get user input and output the result of AI prediction and real
 * results.
 */

#include "frontend.hpp"
#include "generate.hpp"
#include "utils.hpp"
#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

int main() {
    const auto dataset_type = smart_sort::getDatasetType();
    const int dataset_size = smart_sort::getDatasetSize();
    std::vector<int> data(dataset_size);
    smart_sort::generateByType(data, dataset_type);
    const auto algorithm_performance_ascending =
        smart_sort::getAllAlgorithmPerformance(data, 1);
    const auto algorithm_performance_descending =
        smart_sort::getAllAlgorithmPerformance(data, -1);
    const std::string AI_best_choice_ascending =
        smart_sort::getAIBestChoice(data, 1);
    const std::string AI_best_choice_descending =
        smart_sort::getAIBestChoice(data, -1);
    const std::string actual_best_choice_ascending =
        (*std::max_element(algorithm_performance_ascending.begin(),
                           algorithm_performance_ascending.end(),
                           [](const auto & a, const auto & b) {
                               return a.execution_time > b.execution_time;
                           }))
            .name;
    const std::string actual_best_choice_descending =
        (*std::max_element(algorithm_performance_descending.begin(),
                           algorithm_performance_descending.end(),
                           [](const auto & a, const auto & b) {
                               return a.execution_time > b.execution_time;
                           }))
            .name;

    if (data.size() <
        static_cast<size_t>(smart_sort::DATASET_CONSTANT::SMALL_ARRAY_SIZE)) {
        std::cout << "\nOriginal Array:\n"
                  << smart_sort::array2string(data) << "\n";
    }
    std::cout << "\nAlgorithm Performance:\n";
    smart_sort::displayAlgorithmPerformanceInTable(
        algorithm_performance_ascending, algorithm_performance_descending);
    std::cout << "AI-predicted Best Algorithm (Ascending): "
              << AI_best_choice_ascending << "\n"
              << "Actual Best Algorithm (Ascending): "
              << actual_best_choice_ascending << "\n";
    std::cout << "\n";
    std::cout << "AI-predicted Best Algorithm (Descending): "
              << AI_best_choice_descending << "\n"
              << "Actual Best Algorithm (Descending): "
              << actual_best_choice_descending << "\n";
    std::cout.flush();

#ifdef _WIN32
    std::system("pause");
#endif

    return 0;
}

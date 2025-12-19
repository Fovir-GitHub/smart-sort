#include "frontend.hpp"
#include "generate.hpp"
#include "utils.hpp"
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

int main() {
    const auto dataset_type = smart_sort::getDatasetType();
    const int dataset_size = smart_sort::getDatasetSize();
    std::vector<int> data(dataset_size);
    smart_sort::generateByType(data, dataset_type);
    const auto algorithm_performance =
        smart_sort::getAllAlgorithmPerformance(data);
    const std::string AI_best_choice = smart_sort::getAIBestChoice(data);
    const std::string actual_best_choice =
        (*std::max_element(algorithm_performance.begin(),
                           algorithm_performance.end(),
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
    smart_sort::displayAlgorithmPerformanceInTable(algorithm_performance);
    std::cout << "AI-predicted Best Algorithm: " << AI_best_choice << "\n";
    std::cout << "Actual Best Algorithm: " << actual_best_choice << "\n";
    std::cout.flush();

    return 0;
}

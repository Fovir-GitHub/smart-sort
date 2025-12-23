#pragma once

#include "generate.hpp"
#include <string>
#include <utility>
#include <vector>

namespace smart_sort {

/**
 * @class AlgorithmPerformance
 * @brief Structure used to store performance of an algorithm, including the
 * algorithm name, comparison times, and the average execution time.
 */
struct AlgorithmPerformance {
    std::string name;
    int comparisons;
    long long execution_time;

    AlgorithmPerformance(std::string _name, const int _comparisons,
                         const long long _execution_time)
        : name(std::move(_name)), comparisons(_comparisons),
          execution_time(_execution_time) {}
};

void displayDatasetMenu();

DataType getDatasetType();

int getDatasetSize();

std::vector<AlgorithmPerformance>
getAllAlgorithmPerformance(std::vector<int> & arr, int direction = 1);

void displayAlgorithmPerformanceInTable(
    const std::vector<AlgorithmPerformance> & algorithm_performance_ascending,
    const std::vector<AlgorithmPerformance> & algorithm_performance_descending);

} // namespace smart_sort

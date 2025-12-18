#pragma once

#include "generate.hpp"
#include <string>
#include <utility>
#include <vector>

namespace smart_sort {

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
getAllAlgorithmPerformance(std::vector<int> & arr);

void displayAlgorithmPerformanceInTable(
    const std::vector<AlgorithmPerformance> & algorithm_performance);

} // namespace smart_sort

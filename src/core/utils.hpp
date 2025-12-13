#pragma once

#include "sort_algorithm.hpp"
#include <chrono>
#include <functional>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>

namespace smart_sort {

template <typename TYPE>
using AlgorithmMap =
    std::unordered_map<std::string, std::function<void(std::vector<TYPE> &)>>;

const int DEFAULT_RUN_TIMES = 10;

template <typename FUNCTION>
long long measureTime(FUNCTION f) {
    using namespace std::chrono;
    auto start_time = high_resolution_clock::now();
    f();
    auto end_time = high_resolution_clock::now();
    return duration_cast<nanoseconds>(end_time - start_time).count();
}

template <typename FUNCTION>
long double measureAverageTime(FUNCTION f, int times = DEFAULT_RUN_TIMES) {
    long double result = 0.0;
    for (int i = 0; i < times; i++) {
        result += (long double)measureTime(f) / times;
    }
    return result;
}

/**
 * @brief Construct an algorithm map with type and compare function provided.
 *
 * @tparam TYPE Array type.
 * @param cmp Compare function.
 * @return A map contains pairs `<name, sorter>`.
 */
template <typename TYPE, typename COMPARE = std::less<>>
AlgorithmMap<TYPE> getAlgorithmMapByType(COMPARE cmp = std::less<>{}) {
    // More algorithms goes here:
    std::unordered_map<std::string, std::function<void(std::vector<TYPE> &)>>
        result = {
            {"Bubble Sort",
             [cmp](std::vector<TYPE> & v) {
                 smart_sort::bubbleSort(v.begin(), v.end(), cmp);
             }},
            {"Selection Sort",
             [cmp](std::vector<TYPE> & v) {
                 smart_sort::selectionSort(v.begin(), v.end(), cmp);
             }},
            {"Merge Sort",
             [cmp](std::vector<TYPE> & v) {
                 smart_sort::mergeSort(v.begin(), v.end(), cmp);
             }},
            {"Quick Sort",
             [cmp](std::vector<TYPE> & v) {
                 smart_sort::quickSort(v.begin(), v.end(), cmp);
             }},
        };
    return result;
}

std::mt19937 getRandomGenerator();

} // namespace smart_sort

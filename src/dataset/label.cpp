/**
 * @file src/dataset/label.cpp
 * @brief Label data from dataset.
 */

#include "label.hpp"
#include "core/utils.hpp"
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/**
 * @brief Get frequency of each number in an array.
 *
 * @param arr array of numbers
 * @return a hash map in format [number, frequency of number]
 */
static std::unordered_map<int, int> getFrequency(const std::vector<int> & arr) {
    std::unordered_map<int, int> freq;
    for (const auto it : arr) {
        freq[it]++;
    }
    return freq;
}

namespace smart_sort {

/**
 * @brief Get raw data from `ifstream`.
 *
 * @param result an array to store raw data
 * @param fin the `ifstream` with a file opened
 */
void getRawData(Array & result, std::ifstream & fin) {
    std::string line;
    std::getline(fin, line);
    std::istringstream iss(line);
    int n = 0;
    result.clear();
    while (iss >> n) {
        result.push_back(n);
    }
}

/**
 * @brief Label features of a group of data and output them to a file.
 *
 * @param target the data to be labelled
 * @param fout `ofstream` used to output the result to a file
 * @param direction `1` -- sort ascending, `-1` -- sort descending.
 */
void labelData(Array & target, std::ofstream & fout, int direction) {
    const size_t size = target.size();
    const double order_ratio = getOrderRatio(target);
    const double effective_order = order_ratio * direction;
    const double duplicated_rank = getDuplicatedRank(target);
    const double unique_ratio = getUniqueRatio(target);
    const double entropy = getEntroy(target);
    const int value_range =
        static_cast<int>(*std::max_element(target.begin(), target.end()) -
                         *std::min_element(target.begin(), target.end()));
    const double sorted_prefix_length =
        getSortedPrefixLength(target, direction);
    const double sorted_suffix_length =
        getSortedSuffixLength(target, direction);
    const int best_algorithm = getBestAlgorithm(target, direction);

    fout << std::setprecision(std::numeric_limits<double>::max_digits10) << size
         << "," << order_ratio << "," << effective_order << ","
         << duplicated_rank << "," << unique_ratio << "," << entropy << ","
         << value_range << "," << sorted_prefix_length << ","
         << sorted_suffix_length << "," << direction << "," << best_algorithm
         << "\n";
}

/**
 * @brief Calculate the rank of duplicated by
 * total_number_of_duplicated_elements / size.
 *
 * @param source array of data
 * @return duplicated rank
 */
double getDuplicatedRank(const Array & source) {
    if (source.empty()) {
        return 0;
    }
    size_t result = 0;
    for (const auto & [_, v] : getFrequency(source)) {
        result += v > 1 ? v - 1 : 0;
    }
    return static_cast<double>(result) / static_cast<double>(source.size());
}

/**
 * @brief Calculate the unique ratio by
 * number_of_unique_elements / size
 *
 * @param source array of data
 * @return unique ratio
 */
double getUniqueRatio(const Array & source) {
    const std::unordered_set<int> set(source.begin(), source.end());
    return !source.empty() ? static_cast<double>(set.size()) /
                                 static_cast<double>(source.size())
                           : 0;
}

/**
 * @brief Calculate the entroy of a group of data.
 *
 * @param source array of data
 * @return the entroy of data
 */
double getEntroy(const Array & source) {
    const int n = (int)source.size();
    if (n <= 0) {
        return 0;
    }

    double entropy = 0.0;

    // Get probabilities of elements.
    const auto freq = getFrequency(source);
    std::vector<double> prob(freq.size());
    for (const auto & [_, v] : freq) {
        prob.push_back((double)v / n);
    }
    for (const auto p : prob) {
        if (p > 0) {
            entropy += p * std::log2(p);
        }
    }

    return -entropy;
}

/**
 * @brief Calculate the order ratio by
 * (ascending_pairs / size) - (descending_pairs / size).
 *
 * @param source data of arry
 * @return order ratio of data
 */
double getOrderRatio(const Array & source) {
    // Number of pairs is the size of the array - 1.
    const size_t n = source.size() - 1;
    if (n <= 0) {
        return 1;
    }

    int increase = 0;
    int decrease = 0;
    for (size_t i = 0; i < n; i++) {
        if (source[i] < source[i + 1]) {
            increase++;
        } else if (source[i] > source[i + 1]) {
            decrease++;
        }
    }

    auto size = static_cast<int>(n);
    return (static_cast<double>(increase) / size) -
           (static_cast<double>(decrease) / size);
}

/**
 * @brief Get the maximum length of sorted prefix-array.
 *
 * @param source array of data
 * @param direction `1` -- ascending, `-1` -- descending
 * @return length / size
 */
double getSortedPrefixLength(const Array & source, int direction) {
    const int n = (int)source.size();
    if (n < 1) {
        return 0;
    }

    int counter = 1;
    for (int i = 1; i < n && (source[i] - source[i - 1]) * direction > 0; i++) {
        counter++;
    }
    return static_cast<double>(counter) / n;
}

/**
 * @brief Get the maximum length of sorted suffix-array.
 *
 * @param source array of data
 * @param direction `1` -- ascending, `-1` -- descending
 * @return length / size
 */
double getSortedSuffixLength(const Array & source, int direction) {
    const int n = (int)source.size();
    if (n < 1) {
        return 0;
    }

    int counter = 1;
    for (int i = n - 2; i >= 0 && (source[i + 1] - source[i]) * direction > 0;
         i--) {
        counter++;
    }
    return static_cast<double>(counter) / n;
}

/**
 * @brief Get the best sorting algorithm for the given data.
 *
 * @param source array of data
 * @param direction `1` -- ascending, `-1` -- descending
 * @return the best sorting algorithm:
 *      - `1` --  Bubble Sort
 *      - `2` --  Insertion Sort
 *      - `3` --  Merge Sort
 *      - `4` --  Quick Sort
 */
int getBestAlgorithm(Array & source, int direction) {
    auto cmp = direction > 0 ? std::function<bool(int, int)>(std::less<>{})
                             : std::function<bool(int, int)>(std::greater<>{});
    auto algorithm_map = smart_sort::getAlgorithmMapByType<int>(cmp);
    std::string result;
    long double faster = std::numeric_limits<long double>::max();
    for (const auto & [name, func] : algorithm_map) {
        // Skip bubble sort and insertion sort when the size is larger than
        // `1000` to reduce the time cost.
        // NOLINTNEXTLINE
        if (source.size() > 1000 &&
            (name == "Bubble Sort" || name == "Insertion Sort")) {
            continue;
        }

        const long double current = smart_sort::measureAverageTime(
            [source, func]() mutable { func(source); });
        if (current < faster) {
            faster = current;
            result = name;
        }
    }

    if (result == "Bubble Sort") {
        return 1;
    }
    if (result == "Insertion Sort") {
        return 2;
    }
    if (result == "Merge Sort") {
        return 3;
    }

    // Quick Sort
    return 4;
}

} // namespace smart_sort

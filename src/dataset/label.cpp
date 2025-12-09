#include "label.hpp"
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

static std::unordered_map<int, int> getFrequency(const std::vector<int> & arr) {
    std::unordered_map<int, int> freq;
    for (const auto it : arr) {
        freq[it]++;
    }
    return freq;
}

namespace smart_sort {

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

void labelData(const Array & target, std::ofstream & fout, int direction) {
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

    fout << std::setprecision(std::numeric_limits<double>::max_digits10) << size
         << " " << order_ratio << " " << effective_order << " "
         << duplicated_rank << " " << unique_ratio << " " << entropy << " "
         << value_range << " " << sorted_prefix_length << " "
         << sorted_suffix_length << " " << direction << " ";
    for (const auto & num : target) {
        fout << num << " ";
    }
    fout << "\n";
}

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

double getUniqueRatio(const Array & source) {
    const std::unordered_set<int> set(source.begin(), source.end());
    return !source.empty() ? static_cast<double>(set.size()) /
                                 static_cast<double>(source.size())
                           : 0;
}

double getEntroy(const Array & source) {
    const int n = (int)source.size();
    if (n <= 0) {
        return 0;
    }

    double entropy = 0.0;
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

double getOrderRatio(const Array & source) {
    const size_t n = source.size() - 1;
    if (n <= 0) {
        return 1;
    }

    int increase = 0;
    int decrease = 0;
    for (int i = 0; i < n; i++) {
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

} // namespace smart_sort

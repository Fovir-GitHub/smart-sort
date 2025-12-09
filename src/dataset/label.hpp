#pragma once

#include <cstddef>
#include <fstream>
#include <vector>

namespace smart_sort {

using Array = std::vector<int>;

void getRawData(Array & result, std::ifstream & fin);

void labelData(const Array & target, std::ofstream & fout, int direction = 1);

size_t getDuplicatedRank(const Array & source);

size_t getUniqueRatio(const Array & source);

double getEntroy(const Array & source);

double getOrderRatio(const Array & source);

size_t getSortedPrefixLength(const Array & source, int direction);

size_t getSortedSuffixLength(const Array & source, int direction);

} // namespace smart_sort

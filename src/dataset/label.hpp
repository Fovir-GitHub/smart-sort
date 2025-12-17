#pragma once

#include <fstream>
#include <vector>

namespace smart_sort {

using Array = std::vector<int>;

void getRawData(Array & result, std::ifstream & fin);

void labelData(Array & target, std::ofstream & fout, int direction = 1);

double getDuplicatedRank(const Array & source);

double getUniqueRatio(const Array & source);

double getEntroy(const Array & source);

double getOrderRatio(const Array & source);

double getSortedPrefixLength(const Array & source, int direction);

double getSortedSuffixLength(const Array & source, int direction);

int getBestAlgorithm(Array & source, int direction);

} // namespace smart_sort

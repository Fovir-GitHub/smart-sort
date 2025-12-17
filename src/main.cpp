#include "core/sort_algorithm.hpp"
#include <iostream>
#include <vector>

int main() {
    // NOLINTNEXTLINE
    std::vector<int> nums = {2, 3, 6, 4, 1};
    smart_sort::bubbleSort(nums.begin(), nums.end());

    for (const auto & num : nums) {
        std::cout << num << ' ';
    }
    std::cout << '\n';

    return 0;
}

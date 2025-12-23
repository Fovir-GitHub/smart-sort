#pragma once

#include <algorithm>
#include <cstddef>
#include <functional>
#include <iterator>
#include <utility>
#include <vector>

namespace smart_sort {
/**
 * @brief Bubble sort using early termination
 *
 * @tparam Iter forward iterator type
 * @tparam Compare comparator type: default is std::less<>(acsending)
 * @param start begin iterator
 * @param end ending iterator
 * @param cmp comparison function
 **/
template <typename Iter, typename Compare = std::less<>>
void bubbleSort(Iter start, Iter end, Compare cmp = std::less<>{}) {
    if (start >= end) { // Check if the traversal has ended.
        return;
    }

    bool swapped =
        true; // Flag to check if any swaps occurred during the current pass
              // If swapped == true -->  enter the next iteration of for loop
              // If swapped == false --> already sorted. Exit the loop early to
              // save the running time
    for (Iter i = end; i >= start && swapped; i--) {
        swapped = false;
        for (Iter j = start; j != i - 1; j++) {
            if (cmp(*(j + 1), *j)) {
                std::swap(*j, *(j + 1));
                swapped = true;
            }
        }
    }
}

/**
 * @brief Selection Sort
 *
 * @tparam Iter forward iterator type
 * @tparam Compare comparator type: default is std::less<>(acsending)
 * @param start begin iterator
 * @param end ending iterator
 * @param cmp comparison function
 */
template <typename Iter, typename Compare = std::less<>>
void insertionSort(Iter start, Iter end, Compare cmp = std::less<>{}) {
    if (start >= end) {
        return;
    }

    for (Iter i = start + 1; i != end; i++) {
        auto base = *i;
        Iter j = i - 1;
        while (j >= start && cmp(base, *j)) {
            *(j + 1) = *j;
            j--;
        }
        *(j + 1) = base;
    }
}

/**
 * @brief merging phase of merge sort
 *
 * @tparam Iter forward iterator type
 * @tparam Compare comparator type: default is std::less<>(acsending)
 * @param start begin iterator
 * @param mid the middle split iterator
 * @param end ending iterator
 * @param cmp comparison function
 */
template <typename Iter, typename Compare = std::less<>>
void merge(Iter start, Iter mid, Iter end, Compare cmp = std::less<>{}) {
    using ValueType = typename std::iterator_traits<Iter>::value_type;
    // Divide the vector into two parts: left part and right part
    std::vector<ValueType> left_temp(start, mid);
    std::vector<ValueType> right_temp(mid, end);
    // Initialize the start index of each part
    size_t i = 0;
    size_t j = 0;
    Iter k = start;
    // Compare and copy the smaller value of left part and right part to the
    // temporary container
    while (i < left_temp.size() && j < right_temp.size()) {
        if (cmp(right_temp[j], left_temp[i])) {
            *k = right_temp[j++];
        } else {
            *k = left_temp[i++];
        }
        k++;
    }
    // Copy the remaining part of left vector to the temporary container
    while (i < left_temp.size()) {
        *k++ = left_temp[i++];
    }
    // Copy the remaining part of right vector to the temporary container
    while (j < right_temp.size()) {
        *k++ = right_temp[j++];
    }
}
/**
 * @brief partiton phase of the merge sort
 *
 * @tparam Iter forward iterator type
 * @tparam Compare comparator type: default is std::less<>(acsending)
 * @param start begin iterator
 * @param end ending iterator
 * @param cmp comparison function
 */
template <typename Iter, typename Compare = std::less<>>
void mergeSort(Iter start, Iter end, Compare cmp = std::less<>{}) {
    if (std::distance(start, end) <= 1) {
        return;
    }

    Iter mid = start;
    std::advance(mid, std::distance(start, end) / 2);
    // Split
    mergeSort(start, mid, cmp);
    mergeSort(mid, end, cmp);
    // Merge
    merge(start, mid, end, cmp);
}
/**
 * @brief Sentinel partitioning of quick sort
 *
 * @tparam Iter forward iterator type
 * @tparam Compare comparator type: default is std::less<>(acsending)
 * @param start begin iterator
 * @param end ending iterator
 * @param cmp comparison function
 * @return Iter
 */
template <typename Iter, typename Compare = std::less<>>
Iter partition(Iter start, Iter end, Compare cmp = std::less<>{}) {
    if (start >= end) {
        return start;
    }

    using ValueType = typename std::iterator_traits<Iter>::value_type;
    ValueType pivot_value = *start;
    Iter i = start;
    Iter j = end;

    while (i != j) {
        while (i != j && !cmp(*j, pivot_value)) {
            j--; // Find the first element less than the pivot from right to
                 // left
        }
        while (i != j && !cmp(pivot_value, *i)) {
            i++; // Find the first element greater than the pivot from left to
                 // right
        }
        if (i != j) {
            std::iter_swap(i, j);
        }
    }
    std::iter_swap(start, i);
    return i;
}
/**
 * @brief Quick sort
 *
 * @tparam Iter forward iterator type
 * @tparam Compare comparator type: default is std::less<>(acsending)
 * @param start begin iterator
 * @param end ending iterator
 * @param cmp comparison function
 */
template <typename Iter, typename Compare = std::less<>>
void quickSort(Iter start, Iter end, Compare cmp = std::less<>{}) {
    if (std::distance(start, end) <= 1) {
        return;
    }

    Iter last_element = std::prev(end);
    // Sentinel partitionning
    Iter pivot_final_pos = smart_sort::partition(start, last_element, cmp);
    Iter next_to_pivot = std::next(pivot_final_pos);

    // recursion
    quickSort(start, pivot_final_pos, cmp);
    quickSort(next_to_pivot, end, cmp);
}

} // namespace smart_sort

// namepace smart_sort

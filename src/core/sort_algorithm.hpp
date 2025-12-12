#pragma once

#include <algorithm>
#include <cstddef>
#include <functional>
#include <iterator>
#include <utility>
#include <vector>

namespace smart_sort {

template <typename Iter, typename Compare = std::less<>>
void bubbleSort(Iter start, Iter end, Compare cmp = std::less<>{}) {
    if (start >= end) {
        return;
    }

    bool swapped = true;
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

template <typename Iter, typename Compare = std::less<>>
void selectionSort(Iter start, Iter end, Compare cmp = std::less<>{}) {
    if (start == end) {
        return;
    }

    for (Iter i = start; i != end; i++) {
        Iter k = i;
        for (Iter j = std::next(i); j != end; j++) {
            if (cmp(*j, *k)) {
                k = j;
            }
        }
        std::swap(*i, *k);
    }
}

template <typename Iter, typename Compare = std::less<>>
void merge(Iter start, Iter mid, Iter end, Compare cmp = std::less<>{}) {
    using ValueType = typename std::iterator_traits<Iter>::value_type;
    std::vector<ValueType> left_temp(start, mid);
    std::vector<ValueType> right_temp(mid, end);
    size_t i = 0;
    size_t j = 0;
    Iter k = start;

    while (i < left_temp.size() && j < right_temp.size()) {
        if (cmp(right_temp[j], left_temp[i])) {
            *k = right_temp[j++];
        } else {
            *k = left_temp[i++];
        }
        k++;
    }

    while (i < left_temp.size()) {
        *k++ = left_temp[i++];
    }

    while (j < right_temp.size()) {
        *k++ = right_temp[j++];
    }
}

template <typename Iter, typename Compare = std::less<>>
void mergeSort(Iter start, Iter end, Compare cmp = std::less<>{}) {
    if (std::distance(start, end) <= 1) {
        return;
    }

    Iter mid = start;
    std::advance(mid, std::distance(start, end) / 2);
    mergeSort(start, mid, cmp);
    mergeSort(mid, end, cmp);
    merge(start, mid, end, cmp);
}

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
            j--;
        }
        while (i != j && !cmp(pivot_value, *i)) {
            i++;
        }
        if (i != j) {
            std::iter_swap(i, j);
        }
    }
    std::iter_swap(start, i);
    return i;
}

template <typename Iter, typename Compare = std::less<>>
void quickSort(Iter start, Iter end, Compare cmp = std::less<>{}) {
    if (std::distance(start, end) <= 1) {
        return;
    }

    Iter last_element = std::prev(end);
    Iter pivot_final_pos = smart_sort::partition(start, last_element, cmp);
    Iter next_to_pivot = std::next(pivot_final_pos);

    quickSort(start, pivot_final_pos, cmp);
    quickSort(next_to_pivot, end, cmp);
}

} // namespace smart_sort

// namepace smart_sort

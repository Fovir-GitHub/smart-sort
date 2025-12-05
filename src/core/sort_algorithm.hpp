#pragma once

#include <functional>
#include <utility>

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

} // namespace smart_sort

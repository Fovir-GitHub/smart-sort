#pragma once

#include "utils.h"
#include <functional>
#include <utility>

SMART_SORT_NAMESPACE_BEGIN

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

SMART_SORT_NAMESPACE_END

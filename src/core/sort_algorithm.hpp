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

template <typename Iter, typename Compare = std::less<>>
void selectionSort(Iter start, Iter end, Compare cmp = std::less<>{}) {
    if(start == end){
        return;
    }
    for (Iter i = start; i != end; i++) {
        Iter k = i;
        for (Iter j = std::next(i); j != end; j++) {
            if (cmp(*j, *k))
                k = j; 
        }
        std::swap(*i, *k);
    }
}

template <typename Iter, typename Compare = std::less<>>
void merge(Iter start, Iter mid, Iter end ,Compare cmp = std::less<>{}) {

    using ValueType = typename std::iterator_traits<Iter>::value_type;

    std::vector<ValueType> left_temp(start, mid);
    std::vector<ValueType> right_temp(mid, end);

    size_t i = 0;         
    size_t j = 0;         
    Iter k = start;
    while (i < left_temp.size() && j < right_temp.size()) {

        if (cmp(right_temp[j], left_temp[i])) { 
            *k = right_temp[j];
            j++;
        } else {
          
            *k = left_temp[i];
            i++;
        }
        k++; 
    }
    while (i < left_temp.size()) {
        *k = left_temp[i];
        i++;
        k++;
    }


    while (j < right_temp.size()) {
        *k = right_temp[j];
        j++;
        k++;
    }
   
}

template <typename Iter, typename Compare = std::less<>>
void mergeSort(Iter start, Iter end, Compare cmp = std::less<>{}) {
    if(std::distance(start, end) <= 1){
        return;
    }
    Iter mid = start;
    std::advance(mid, std::distance(start, end) / 2);
    mergeSort(start, mid, cmp);
    mergeSort(mid, end, cmp);
    merge(start, mid, end, cmp);
}


template <typename Iter, typename Compare = std::less<>>
void quickSort(Iter start, Iter end, Compare cmp = std::less<>{}) {}

} // namespace smart_sort

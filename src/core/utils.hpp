#include <chrono>

namespace smart_sort {

const int DEFAULT_RUN_TIMES = 10;

template <typename FUNCTION>
long long measureTime(FUNCTION f) {
    using namespace std::chrono;
    auto start_time = high_resolution_clock::now();
    f();
    auto end_time = high_resolution_clock::now();
    return duration_cast<nanoseconds>(end_time - start_time).count();
}

template <typename FUNCTION>
long double measureAverageTime(FUNCTION f, int times = DEFAULT_RUN_TIMES) {
    long double result = 0.0;
    for (int i = 0; i < times; i++) {
        result += (long double)measureTime(f) / times;
    }
    return result;
}

} // namespace smart_sort

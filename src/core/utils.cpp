#include "utils.hpp"
#include <random>

namespace smart_sort {

std::mt19937 getRandomGenerator() {
    std::random_device rd;
    std::mt19937 gen(rd());
    return gen;
}

} // namespace smart_sort

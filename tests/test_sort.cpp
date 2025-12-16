#include "core/sort_algorithm.hpp"
#include <algorithm>
#include <functional>
#include <gtest/gtest.h>
#include <random>
#include <sched.h>
#include <string>
#include <unordered_map>
#include <vector>

const static int LOWER_BOUNDARY = 1;
const static int UPPER_BOUNDARY = 100;
const static int TEST_GROUPS = 10;
const static int ARRAY_MAX_SIZE = 10000;

// Alias
template <typename TYPE>
using AlgorithmMap =
    std::unordered_map<std::string, std::function<void(std::vector<TYPE> &)>>;

static std::mt19937 getRandomGenerator() {
    std::random_device rd;
    std::mt19937 gen(rd());
    return gen;
}

/**
 * @brief Check whether two arrays are equal by using GTest.
 *
 * @tparam TYPE Array type.
 */
template <typename TYPE>
void checkEqualArrays(const std::vector<TYPE> & a, const std::vector<TYPE> & b,
                      const std::string & name) {
    ASSERT_EQ(a.size(), b.size()) << "Arrays have different sizes";
    for (size_t i = 0; i < a.size(); i++) {
        EXPECT_EQ(a[i], b[i]) << "Mismatch at index " << i << "\n"
                              << name << " failed!";
    }
}

/**
 * @brief Construct an algorithm map with type and compare function provided.
 *
 * @tparam TYPE Array type.
 * @param cmp Compare function.
 * @return A map contains pairs `<name, sorter>`.
 */
template <typename TYPE, typename COMPARE = std::less<>>
AlgorithmMap<TYPE> getAlgorithmMapByType(COMPARE cmp = std::less<>{}) {
    // More algorithms goes here:
    std::unordered_map<std::string, std::function<void(std::vector<TYPE> &)>>
        result = {
            {"Bubble Sort",
             [cmp](std::vector<TYPE> & v) {
                 smart_sort::bubbleSort(v.begin(), v.end(), cmp);
             }},
            {"Selection Sort",
             [cmp](std::vector<TYPE> & v) {
                 smart_sort::selectionSort(v.begin(), v.end(), cmp);
             }},
            {"Insertion Sort",
             [cmp](std::vector<TYPE> & v) {
                 smart_sort::insertionSort(v.begin(), v.end(), cmp);
             }},
            {"Merge Sort",
             [cmp](std::vector<TYPE> & v) {
                 smart_sort::mergeSort(v.begin(), v.end(), cmp);
             }},
            {"Quick Sort",
             [cmp](std::vector<TYPE> & v) {
                 smart_sort::quickSort(v.begin(), v.end(), cmp);
             }},
        };
    return result;
}

/**
 * @brief Test algorithm provided.
 *
 * @tparam TYPE Data type.
 * @tparam DIST Distribution type.
 * @param gen Random variable generator.
 * @param dist Distribution.
 * @param algorithm_map A map in `<name, sorter>` format.
 * @param cmp Compare function.
 * @param array_max_size The maximum size of testing arrays.
 */
template <typename TYPE, typename DIST, typename COMPARE = std::less<>>
void testAlgorithm(std::mt19937 & gen, DIST & dist,
                   const AlgorithmMap<TYPE> & algorithm_map,
                   COMPARE cmp = std::less<>{},
                   const int array_max_size = ARRAY_MAX_SIZE) {
    std::vector<TYPE> expected;
    for (const auto & [name, func] : algorithm_map) {
        for (int i = 0; i < TEST_GROUPS + 3; i++) {
            int size = static_cast<int>(dist(gen)) % array_max_size;
            if (i >= TEST_GROUPS) {
                size = i - TEST_GROUPS;
            }
            expected.resize(size);
            std::generate(expected.begin(), expected.end(), gen);
            std::vector<TYPE> data(expected.begin(), expected.end());
            func(data);
            std::sort(expected.begin(), expected.end(), cmp);
            checkEqualArrays(data, expected, name);
        }
    }
}

/**
 * @brief Test sort algorithms with different types, distribution types, and
 * compare functions.
 *
 * @tparam TYPE Data type.
 * @tparam DIST_TYPE Tyep of distributions.
 * @param cmp Compare function.
 */
template <typename TYPE, typename DIST_TYPE, typename COMPARE = std::less<>>
void runTest(COMPARE cmp = std::less<>{}) {
    std::mt19937 gen = getRandomGenerator();
    DIST_TYPE dist(LOWER_BOUNDARY, UPPER_BOUNDARY);
    auto algorithm_map = getAlgorithmMapByType<int>(cmp);
    testAlgorithm(gen, dist, algorithm_map, cmp);
}

TEST(SortTest, SortIntegerAscending) {
    runTest<int, std::uniform_int_distribution<>>();
}

TEST(SortTest, SortIntegerDescending) {
    runTest<int, std::uniform_int_distribution<>>(std::greater<>{});
}

TEST(SortTest, SortFloatingNumberAscending) {
    runTest<double, std::uniform_real_distribution<>>();
}

TEST(SortTest, SortFloatingNumberDescending) {
    runTest<double, std::uniform_real_distribution<>>(std::greater<>{});
}

int main(int argc, char ** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

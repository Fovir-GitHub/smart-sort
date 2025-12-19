#include "utils.hpp"
#include <array>
#include <cstdio>
#include <iostream>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace smart_sort {

std::mt19937 getRandomGenerator() {
    std::random_device rd;
    std::mt19937 gen(rd());
    return gen;
}

std::string array2string(const std::vector<int> & arr) {
    std::ostringstream oss;
    oss << "[";
    for (int i = 0; i < arr.size(); i++) {
        oss << arr[i] << ((i == arr.size() - 1) ? "]" : ",");
    }
    return oss.str();
}

std::string getAIBestChoice(const std::vector<int> & arr) {
    const static int BUFFER_SIZE = 128;
    const static std::vector<std::string> ALGORITHMS = {
        "Bubble Sort",
        "Insertion Sort",
        "Merge Sort",
        "Quick Sort",
    };

#ifdef _WIN32
#define popen _popen
#define pclose _pclose
    const std::string redirect = " 2>null";
#else
    const std::string redirect = " 2>/dev/null";
#endif

    const std::string cmd = "python3 MLmodel/predict_api.py \'" +
                            array2string(arr) + "\' 1" + redirect;

    // NOLINTNEXTLINE
    FILE * pipe = popen(cmd.c_str(), "r");
    if (!pipe) {
        throw std::runtime_error("popen failed");
    }

    std::array<char, BUFFER_SIZE> buffer{};
    std::string result;

    while (fgets(buffer.data(), sizeof(buffer), pipe)) {
        result += buffer.data();
    }

    // NOLINTNEXTLINE
    pclose(pipe);

    return ALGORITHMS[std::stoi(result) - 1];
}

} // namespace smart_sort

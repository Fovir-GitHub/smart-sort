#include "utils.hpp"
#include <array>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace smart_sort {

/**
 * @brief Initialize a random generator.
 *
 * @return The random generator.
 */
std::mt19937 getRandomGenerator() {
    std::random_device rd;
    std::mt19937 gen(rd());
    return gen;
}

/**
 * @brief Convert an array to a string.
 *
 * @param arr Array to be converted.
 * @return A string like "[1,2,3,4]".
 */
std::string array2string(const std::vector<int> & arr) {
    std::ostringstream oss;
    oss << "[";
    for (int i = 0; i < arr.size(); i++) {
        oss << arr[i] << ((i == arr.size() - 1) ? "]" : ",");
    }
    return oss.str();
}

/**
 * @brief Call Python API to get the best sorting algorithm from AI.
 *
 * @param arr Array to be sorted.
 * @param direction Determine the sorting direction is ascending or descending.
 * @return The name of the best sorting algorithm.
 */
std::string getAIBestChoice(const std::vector<int> & arr, const int direction) {
    const static int BUFFER_SIZE = 128;
    const static std::vector<std::string> ALGORITHMS = {
        "Bubble Sort",
        "Insertion Sort",
        "Merge Sort",
        "Quick Sort",
    };

    // Create a temp file to store data to avoid `popen()` being failed.
    const auto temp_dir = std::filesystem::temp_directory_path() / "smart-sort";
    std::filesystem::create_directory(temp_dir);
    const std::string temp_file = (temp_dir / "data.csv").string();
    std::ofstream fout(temp_file);
    if (fout.fail()) {
        throw std::runtime_error("Failed to create temp file");
    }
    fout << array2string(arr) << "\n";
    fout.close();

    // Ignore warnings or errors from Python API by redicting them to `null`
    // device.
#ifdef _WIN32
#define popen _popen
#define pclose _pclose
    const std::string redirect = " 2>null";
#else
    const std::string redirect = " 2>/dev/null";
#endif

    // Command used to call Python API.
    const std::string cmd = "python MLmodel/predict_api.py " + temp_file + " " +
                            std::to_string(direction) + redirect;

    // Read the result.
    FILE * pipe = popen(cmd.c_str(), "r"); // NOLINT
    if (!pipe) {
        std::filesystem::remove_all(temp_dir);
        throw std::runtime_error("popen failed");
    }

    std::array<char, BUFFER_SIZE> buffer{};
    std::string result;

    while (fgets(buffer.data(), sizeof(buffer), pipe)) {
        result += buffer.data();
    }

    // Close the pipe and remove the temp file.
    pclose(pipe); // NOLINT
    std::filesystem::remove_all(temp_dir);

    return ALGORITHMS[std::stoi(result) - 1];
}

} // namespace smart_sort

#include "generate.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char ** argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " /path/to/output/file\n";
        return -1;
    }

    const std::string filepath = argv[1];
    std::ofstream fout(filepath);
    if (!fout.is_open()) {
        std::cerr << "Failed to open " << filepath << " for writing.\n";
        return -1;
    } // Error

    const int samplesPerType = static_cast<int>(
        smart_sort::DATASET_CONSTANT::DEFAULT_SAMPLE_SIZE); // every type of
                                                            // data, we generate
                                                            // 20,000 samples
    int sampleId = 0;
    for (int t = 0; t < static_cast<int>(
                            smart_sort::DATASET_CONSTANT::NUMBER_OF_DATA_TYPE);
         ++t) {
        auto type = static_cast<smart_sort::DataType>(t);
        for (int k = 0; k < samplesPerType; ++k) {
            // large size or normal size
            const int n = smart_sort::generateSizeForType(type);
            std::vector<int> arr(n);

            // generate data
            smart_sort::generateByType(arr, type);

            // edit CSV
            for (const auto & data : arr) {
                fout << data << " ";
            }
            fout << "\n";
            sampleId++;
        }

        // for (int k = 0; k < samples; ++k) {
        //     // large size or normal size
        //     int n = (smart_sort::generateSizeForType(type) %
        //              static_cast<int>(smart_sort::DATASET_CONSTANT::SMALL_ARRAY_SIZE))
        //              +
        //             1;
        //     if (type == smart_sort::DataType::LargeRandom) {
        //         n = generateSizeForType(type);
        //     }
        //
        //     std::vector<int> arr(n);
        //
        //     // generate data
        //     smart_sort::generateByType(arr, type);
        //
        //     // edit CSV
        //     for (int idx = 0; idx < n; ++idx) {
        //         fout << arr[idx] << " "; // value
        //     }
        //     sampleId++;
        //     fout << "\n";
        // }
    }

    fout.close();
    std::cout << "Data written to " << filepath << "\n";
    return 0;
}

#include "frontend.hpp"
#include "dataset/generate.hpp"
#include <iostream>
#include <string>

namespace smart_sort {

void displayDatasetMenu() {
    const int MENU_BORDER_DEFAULT_LENGTH = 20;
    const auto PRINT_BORDER = [MENU_BORDER_DEFAULT_LENGTH](char ch) {
        std::cout << std::string(MENU_BORDER_DEFAULT_LENGTH, ch) << "\n";
    };

    PRINT_BORDER('=');
    std::cout << "Dataset Types\n";
    PRINT_BORDER('-');
    for (int i = 0; i < static_cast<int>(
                            smart_sort::DATASET_CONSTANT::NUMBER_OF_DATA_TYPE);
         i++) {
        std::cout << "[" << i + 1 << "] "
                  << smart_sort::dataTypeToString(
                         static_cast<smart_sort::DataType>(i))
                  << "\n";
    }
    PRINT_BORDER('=');
}

} // namespace smart_sort

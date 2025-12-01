# src/core/CMakeLists.txt

add_library(
  core

# Source Code Here (Only *.cpp and *.hpp)
  sort_algorithm.hpp
)

target_include_directories(
  core
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)

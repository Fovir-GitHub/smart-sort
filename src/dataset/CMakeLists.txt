# src/dataset/CMakeLists.txt

add_library(
  dataset

# Source Code Here (Only *.cpp and *.hpp)
  generate.cpp
)

target_include_directories(
  dataset
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)

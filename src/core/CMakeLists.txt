# src/core/CMakeLists.txt

add_library(
  core

# Source Code Here (Only *.cpp)
  add.cpp
)

target_include_directories(
  core
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)

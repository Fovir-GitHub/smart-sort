# src/core/CMakeLists.txt

add_library(
  core

# Source Code Here (Only *.cpp and *.hpp)
  utils.hpp
  utils.cpp
  sort_algorithm.hpp
  frontend.cpp
)

target_include_directories(
  core
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(core PRIVATE dataset)

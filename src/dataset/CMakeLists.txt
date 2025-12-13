# src/dataset/CMakeLists.txt

add_library(
  dataset

# Source Code Here (Only *.cpp and *.hpp)
  generate.cpp
  label.cpp
)

target_include_directories(
  dataset
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/src
)

add_executable(feature_extractor feature_extractor.cpp)

target_link_libraries(feature_extractor PRIVATE dataset)


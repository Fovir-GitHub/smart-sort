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
add_executable(generate-answer generate-answer.cpp)
add_executable(generate-dataset generate.cpp)

target_link_libraries(feature_extractor PRIVATE dataset)
target_link_libraries(generate-answer PRIVATE dataset)
target_link_libraries(generate-dataset PRIVATE core dataset)

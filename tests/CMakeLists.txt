# tests/CMakeLists.txt

find_package(GTest REQUIRED)
include(GoogleTest)

set(TEST_BINARY_NAME tests)
file(GLOB TEST_FILES "test_*.cpp")

add_executable(${TEST_BINARY_NAME} ${TEST_FILES})

target_link_libraries(
  ${TEST_BINARY_NAME}
  PRIVATE
  GTest::gtest
  GTest::gtest_main

# Other Modules
  core
)

target_include_directories(
  ${TEST_BINARY_NAME}
  PRIVATE
  ${CMAKE_SOURCE_DIR}/src
)

gtest_discover_tests(${TEST_BINARY_NAME})

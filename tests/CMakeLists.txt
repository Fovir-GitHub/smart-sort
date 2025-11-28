# tests/CMakeLists.txt

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

include(GoogleTest)

set(TEST_BINARY_NAME tests)
file(GLOB TEST_FILES "test_*.cpp")

add_executable(${TEST_BINARY_NAME} ${TEST_FILES})

target_link_libraries(
  ${TEST_BINARY_NAME}
  PRIVATE
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

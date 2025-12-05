# src/CMakeLists.txt

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC_SRCS)
add_subdirectory(core)
add_subdirectory(dataset)

add_executable(smart-sort ${SRC_SRCS})

target_link_libraries(smart-sort PRIVATE core)

### `CMakeLists.txt`

cmake_minimum_required(VERSION 3.10)

project(SegmentDistance)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES "src/*.h" "src/*.cpp")
file(GLOB TEST_SOURCES "test/*.h" "test/*.cpp")
message(STATUS "SOURCES: ${SOURCES}")
message(STATUS "TEST_SOURCES: ${TEST_SOURCES}")

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
enable_testing()

add_executable(tests ${SOURCES} ${TEST_SOURCES})
set_target_properties(tests PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(tests ${GTEST_LIBRARIES} pthread)
target_include_directories(tests PRIVATE src)

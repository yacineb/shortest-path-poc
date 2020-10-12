cmake_minimum_required(VERSION 3.0.0)
project(shortest_path VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# include(CTest)
# enable_testing()
# add_test(shortest_path_tests tests/unit-tests)
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)

add_executable(shortest_path src/main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

target_compile_options(shortest_path
  PUBLIC $<$<CXX_COMPILER_ID:GNU>: -Wall -Wpedantic>
  PUBLIC $<$<CXX_COMPILER_ID:Clang>: -Wall -Wpedantic>)

cmake_minimum_required(VERSION 3.0.0)
project(n-Queens-Solver VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(n-Queens-Solver main.cpp solution.cpp population.cpp evolution.cpp backtracking.cpp simulatedannealing.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

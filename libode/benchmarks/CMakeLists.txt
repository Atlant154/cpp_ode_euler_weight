cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)

project(ode_bench)

option(BENCHMARK_DOWNLOAD_DEPENDENCIES "Download gBenchmark gTest deps" ON)
option(BENCHMARK_ENABLE_TESTING "Suppressing benchmark's tests" OFF)

add_subdirectory(gbench)
include_directories(gbench/include)

add_executable(ode_bench benchmark.cpp)

target_link_libraries(ode_bench libode)
target_link_libraries(ode_bench benchmark)
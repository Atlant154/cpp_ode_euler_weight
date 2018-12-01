cmake_minimum_required(VERSION 3.12)

project(libode VERSION 1.0.0 DESCRIPTION "Numerical solution of ordinary differential equations.")

set(CMAKE_CXX_STANDARD 14)

add_library(libode SHARED appr_scheme.cpp)

set_target_properties(libode PROPERTIES PUBLIC_HEADER appr_scheme.h)

add_subdirectory(benchmarks)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")

    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -Wall -Wextra -pedantic -g -Wshadow -Wformat=2 -Wconversion \
        -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC \
        -D_FORTIFY_SOURCE=2 -fsanitize=undefined")

    set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -O2 -fno-tree-vectorize -fprofile-use -ftree-loop-vectorize")

endif ()

option(PACKAGE_TESTS "Build the tests" OFF)
if (PACKAGE_TESTS)

    if (CMAKE_CXX_COMPILER_ID MATCHES GNU)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
    endif ()

    enable_testing()
    add_subdirectory(tests)
endif ()
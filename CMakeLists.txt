cmake_minimum_required(VERSION 3.12)
project(mkrb)

set(CMAKE_CXX_STANDARD 17)

add_executable(cpp_ode_euler_weight main.cpp src/appr_scheme.cpp src/appr_scheme.h)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")

    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -std=c++17 -Wall -Wextra -pedantic -g -Wshadow -Wformat=2 -Wconversion \
        -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC \
        -D_FORTIFY_SOURCE=2 -fsanitize=undefined")

    set(CMAKE_CXX_FLAGS_RELEASE "-std=c++17 -DNDEBUG -O2 -fno-tree-vectorize -fprofile-use -ftree-loop-vectorize")

endif ()
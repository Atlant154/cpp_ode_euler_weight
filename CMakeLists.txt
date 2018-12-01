cmake_minimum_required(VERSION 3.12)

project(mmf_ode)
set(CMAKE_CXX_STANDARD 17)

add_executable(mmf_ode main.cpp)

add_subdirectory(libode)

target_link_libraries(mmf_ode libode)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")

    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -Wall -Wextra -pedantic -g -Wshadow -Wformat=2 -Wconversion \
        -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC \
        -D_FORTIFY_SOURCE=2 -fsanitize=undefined")

    set(CMAKE_CXX_FLAGS_RELEASE "-std=c++17 -DNDEBUG -O3 -fno-tree-vectorize -fprofile-use -ftree-loop-vectorize")

endif ()
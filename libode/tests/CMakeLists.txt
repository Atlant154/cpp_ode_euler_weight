cmake_minimum_required(VERSION 3.12)

project(libode_tests)

include(GoogleTest)
add_subdirectory(gtest EXCLUDE_FROM_ALL)

set(gtest_force_shared_crt OFF CACHE BOOL "" FORCE)

macro(package_add_test TESTNAME)
    add_executable(${TESTNAME} ${ARGN})
    target_link_libraries(${TESTNAME} gtest gmock gtest_main libode)
    # gtest_add_tests(${TESTNAME} "" AUTO)
    add_test(NAME ${TESTNAME} COMMAND ${TESTNAME})
    set_target_properties(${TESTNAME} PROPERTIES FOLDER tests)
endmacro()

package_add_test(EulerTest         euler.cpp)
package_add_test(RungeTest         runge.cpp)
package_add_test(WeightTest        weight.cpp)
package_add_test(EulerMidpointTest euler_corrected.cpp)
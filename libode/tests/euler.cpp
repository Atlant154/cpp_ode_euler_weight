#include "gtest/gtest.h"
#include "../appr_scheme.h"

#include <cmath>

inline double heat_sources(double x, double y) {
    double p = 0.5;
    return cos(x) - x * sin(x) + p * pow(y - x * cos(x), 4);
}

inline double exact_solution(double x) {
    return x * cos(x);
}

TEST(EstimateError, LargeSplits) {
    unsigned factor = 2;
    unsigned euler_1_splits = 128;
    unsigned euler_2_splits = euler_1_splits * factor;

    euler_scheme euler_1(euler_1_splits, heat_sources);
    euler_scheme euler_2(euler_2_splits, heat_sources);

    euler_1.get_result(0.0);
    euler_2.get_result(0.0);

    double error_euler_1 = euler_1.get_error(exact_solution);
    double error_euler_2 = euler_2.get_error(exact_solution);

    error_euler_1 *= factor;
    error_euler_1 -= std::numeric_limits<double>::epsilon() * euler_1_splits;

    ASSERT_LE(error_euler_2, error_euler_1);
}

TEST(EstimateError, LittleSplit) {
    unsigned factor = 2;
    unsigned euler_1_splits = 128'000;
    unsigned euler_2_splits = euler_1_splits * factor;

    euler_scheme euler_1(euler_1_splits, heat_sources);
    euler_scheme euler_2(euler_2_splits, heat_sources);

    euler_1.get_result(0.0);
    euler_2.get_result(0.0);

    double error_euler_1 = euler_1.get_error(exact_solution);
    double error_euler_2 = euler_2.get_error(exact_solution);

    error_euler_2 *= factor;
    error_euler_2 -= std::numeric_limits<double>::epsilon() * euler_1_splits;

    ASSERT_LE(error_euler_2, error_euler_1);
}
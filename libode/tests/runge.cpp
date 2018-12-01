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
    unsigned runge_1_split = 128;
    unsigned runge_2_split = runge_1_split * factor;

    runge_kutta_scheme runge_1(runge_1_split, heat_sources);
    runge_kutta_scheme runge_2(runge_2_split, heat_sources);

    runge_1.get_result(0.0);
    runge_2.get_result(0.0);

    double error_runge_1 = runge_1.get_error(exact_solution);
    double error_runge_2 = runge_2.get_error(exact_solution);

    error_runge_2 *= pow(factor, 4);
    error_runge_2 -= std::numeric_limits<double>::epsilon() * runge_2_split;

    ASSERT_LE(error_runge_2, error_runge_1);
}

TEST(EstimateError, LittleSplit) {
    unsigned factor = 2;
    unsigned runge_1_split = 128'000;
    unsigned runge_2_split = runge_1_split * factor;

    runge_kutta_scheme runge_1(runge_1_split, heat_sources);
    runge_kutta_scheme runge_2(runge_2_split, heat_sources);

    runge_1.get_result(0.0);
    runge_2.get_result(0.0);

    double error_runge_1 = runge_1.get_error(exact_solution);
    double error_runge_2 = runge_2.get_error(exact_solution);

    error_runge_2 *= pow(factor, 4);
    error_runge_2 -= std::numeric_limits<double>::epsilon() * runge_2_split;

    ASSERT_LE(error_runge_2, error_runge_1);
}
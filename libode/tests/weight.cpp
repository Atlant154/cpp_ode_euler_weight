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
    unsigned weight_1_split = 128;
    unsigned weight_2_split = weight_1_split * factor;

    weight_scheme weight_1(weight_1_split, heat_sources);
    weight_scheme weight_2(weight_2_split, heat_sources);

    weight_1.get_result(0.0);
    weight_2.get_result(0.0);

    double error_weight_1 = weight_1.get_error(exact_solution);
    double error_weight_2 = weight_2.get_error(exact_solution);

    error_weight_2 *= pow(factor, 4);
    error_weight_2 -= std::numeric_limits<double>::epsilon() * weight_1_split;

    ASSERT_LE(error_weight_2, error_weight_1);
}

TEST(EstimateError, LittleSplit) {
    unsigned factor = 2;
    unsigned weight_1_split = 128'000;
    unsigned weight_2_split = weight_1_split * factor;

    weight_scheme weight_1(weight_1_split, heat_sources);
    weight_scheme weight_2(weight_2_split, heat_sources);

    weight_1.get_result(0.0);
    weight_2.get_result(0.0);

    double error_weight_1 = weight_1.get_error(exact_solution);
    double error_weight_2 = weight_2.get_error(exact_solution);

    error_weight_2 *= pow(factor, 4);
    error_weight_2 -= std::numeric_limits<double>::epsilon() * weight_1_split;

    ASSERT_LE(error_weight_2, error_weight_1);
}
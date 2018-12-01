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

    adams_scheme adams_1(weight_1_split, heat_sources);
    adams_scheme adams_2(weight_2_split, heat_sources);

    adams_1.get_result(0.0);
    adams_2.get_result(0.0);

    double error_adams_1 = adams_1.get_error(exact_solution);
    double error_adams_2 = adams_2.get_error(exact_solution);

    error_adams_2 *= pow(factor, 4);
    error_adams_2 -= std::numeric_limits<double>::epsilon() * weight_2_split;

    ASSERT_LE(error_adams_2, error_adams_1);
}

TEST(EstimateError, LittleSplit) {
    unsigned factor = 2;
    unsigned weight_1_split = 128'000;
    unsigned weight_2_split = weight_1_split * factor;

    adams_scheme adams_1(weight_1_split, heat_sources);
    adams_scheme adams_2(weight_2_split, heat_sources);

    adams_1.get_result(0.0);
    adams_2.get_result(0.0);

    double error_adams_1 = adams_1.get_error(exact_solution);
    double error_adams_2 = adams_2.get_error(exact_solution);

    error_adams_2 *= pow(factor, 4);
    error_adams_2 -= std::numeric_limits<double>::epsilon() * weight_2_split;

    ASSERT_LE(error_adams_2, error_adams_1);
}
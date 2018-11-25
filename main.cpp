#include "src/appr_scheme.h"
#include <iostream>
#include <cmath>
#include <memory>
#include <array>
#include <chrono>

inline double exact_solution(double x)
{
    return x * cos(x);
}

inline double heat_sources(double x, double y)
{
    double p = 0.5;
    return cos(x) - x * sin(x) + p * pow(y - x * cos(x), 4);
}

int main()
{
    auto euler  = std::make_unique<euler_scheme>      (1000, heat_sources);
    auto runge  = std::make_unique<runge_kutta_schene>(1000, heat_sources);
    auto weight = std::make_unique<weight_scheme>     (1000, heat_sources);

    std::array<unsigned, 5> hnums = {10, 256, 512, 1024, 2048};

    std::cout << euler -> get_scheme_name() << std::endl;

    for (const auto &hnum : hnums) {
        euler -> new_split(hnum);
        euler -> get_result(0.0);
        std::cout << "H split number: " << hnum << ". ";
        std::cout << "Error is " << euler -> get_error(exact_solution) << "." << std::endl;
    }

    std::cout << runge -> get_scheme_name() << std::endl;

    for (const auto &hnum : hnums) {
        runge -> new_split(hnum);
        runge -> get_result(0.0);
        std::cout << "H split number: " << hnum << ". ";
        std::cout << "Error is " << runge -> get_error(exact_solution) << "." << std::endl;
    }

    std::cout << weight -> get_scheme_name() << std::endl;

    for (const auto &hnum : hnums) {
        weight -> new_split(hnum);
        runge -> get_result(0.0);
        std::cout << "H split number: " << hnum << ". ";
        std::cout << "Error is " << runge -> get_error(exact_solution) << "." << std::endl;
    }

    return 0;
}
#include "src/appr_scheme.h"
#include <iostream>
#include <cmath>
#include <memory>
#include <array>
#include <chrono>

inline double exact_solution(double x)
{
    return cos(0.5 * M_PI * x);
}

inline double heat_sources(double x)
{
    double p = 1.0;
    return - 0.5 * M_PI * sin((M_PI * x) / 2.0) + p * pow(- cos(0.5 * M_PI * x), 3);
}

int main()
{
    auto exmpl = std::make_unique<euler_scheme>(1000, heat_sources);

    auto start = std::chrono::high_resolution_clock::now();

    auto results = exmpl->get_result(1.0);

    exmpl -> get_result(1.0);

    exmpl -> write_to_file();

    exmpl -> clear_result_vector();

    auto finish = std::chrono::high_resolution_clock::now();

    std::cout << exmpl->get_scheme_name() << std::endl;

    std::cout << "Error is " << exmpl->get_error(exact_solution) << "." << std::endl;

    std::chrono::duration<double, std::milli> diff = finish - start;

    std::cout << "Time: " << diff.count() << "." << std::endl;
}
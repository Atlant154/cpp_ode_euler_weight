#include <memory>

//#include <iostream>
//#include <utility>
//#include <fstream>
//#include <chrono>
//#include <string>
//#include <vector>
//#include <omp.h>
//#include <cmath>
//
//double exact_solution(double x) {
//    return x * cos(x);
//}
//
//double rh_function(double x) {
//    return 2 * x * cos(x) + cos(x) - x * sin(x);
//}
//
//void write_file(const std::vector<std::pair<double, double>> &result, const std::string &filename) {
//    std::fstream result_file;
//    result_file.open(filename, std::ios::out | std::ios::trunc);
//
//    for (const auto &item : result)
//        result_file << item.first << '\t' << item.second << "\n";
//
//    result_file.close();
//}
//
//double get_error(const std::vector<std::pair<double, double>> &appr_result, double const h, double const left) {
//    double error = 0.0;
//    double abs_exact, abs_apr, abs_diff;
//
//    for (unsigned iter = 0; iter < appr_result.size(); ++iter) {
//        abs_exact = fabs(exact_solution(left + iter * h));
//        abs_apr   = fabs(appr_result.at(iter).second);
//        abs_diff  = fabs(abs_exact - abs_apr);
//        error     = abs_diff > error ? abs_diff : error;
//    }
//
//    return error;
//}
//
//void euler_explicit(unsigned const h_num, double const left, double const right) {
//
//    double h = (right - left) / h_num;
//
//    std::vector<std::pair<double, double >> result;
//    result.reserve(h_num + 1);
//
//    /*
//     * Service variables:
//     * x - 0x coordinate, u - 0y coordinate(method approximation values).
//    */
//    double x;
//    double u;
//
//    result.emplace_back(std::make_pair(0.0, 0.0));
//
//    for (unsigned iter = 1; iter <= h_num; ++iter) {
//        x = left + iter * h;
//        u = result.back().second + h * (rh_function(result.back().first) - 2 * result.back().second);
//        result.emplace_back(std::make_pair(x, u));
//    }
//
//    std::string filename = "euler_result_Splits:" + std::to_string(h_num) + ".txt";
//
//    write_file(result, filename);
//
//    auto error = get_error(result, h, left);
//
//    std::cout << "H nodes number: " << h_num << ". Max error is " << error << "." << std::endl;
//}
//
//void weight_scheme(unsigned const h_num, double const left, double const right) {
//
//    double h = (right - left) / h_num;
//
//    std::vector<std::pair<double, double>> result;
//    result.reserve(h_num + 1);
//
//    double x, u;
//
//    result.emplace_back(std::make_pair(left, 0.0));
//    result.emplace_back(std::make_pair(h, h * rh_function(left)));
//
//    double sigma = 1.0;
//
//    for (unsigned iter = 2; iter <= h_num; ++iter) {
//        x  = left + iter * h;
//        u  = result.back().second * ((2 - 2 * sigma - 4 * h) / (2 - sigma));
//        u += result.at(iter - 2).second * sigma / (2 - sigma);
//        u += 2 * h * rh_function(result.at(iter - 1).first) / (2 - sigma);
//        result.emplace_back(std::make_pair(x, u));
//    }
//
//    std::string filename = "weight_scheme_Splits:" + std::to_string(h_num) + ".txt";
//
//    write_file(result, filename);
//
//    auto error = get_error(result, h, left);
//
//    std::cout << "H nodes number: " << h_num << ". Max error is " << error << "." << std::endl;
//}
//
//void runge_kutta(unsigned const h_num, double const left, double const right) {
//
//    double h = (right - left) / h_num;
//
//    std::vector<std::pair<double, double>> result;
//    result.reserve(h_num + 1);
//
//    result.emplace_back(std::make_pair(left + 0.0, 0.0));
//
//    double k1, k2, k3, k4;
//
//    double x, u;
//
//    for (unsigned iter = 1; iter <= h_num; ++iter) {
//        k1 = h * (rh_function(result.back().first)           - 2 * result.back().second);
//        k2 = h * (rh_function(result.back().first + h / 2.0) - 2 * result.back().second);
//        k3 = h * (rh_function(result.back().first + h / 2.0) - 2 * result.back().second);
//        k4 = h * (rh_function(result.back().first + h)       - 2 * result.back().second);
//        x = left + iter * h;
//        u = result.back().second + (k1 + 2 * k2 + 2 * k3 + k4) / 6.0;
//        result.emplace_back(std::make_pair(x, u));
//    }
//
//    std::string filename = "runge_kutta_Splits:" + std::to_string(h_num) + ".txt";
//
//    write_file(result, filename);
//
//    auto error = get_error(result, h, left);
//
//    std::cout << "H nodes number: " << h_num << ". Max error is " << error << "." << std::endl;
//}
//
//int main() {
//
//    const double left = 0.0;
//    const double right = 1.0;
//
//    std::vector<unsigned> h_nums = {1310000, 1310000, 1310000, 1310000, 1310000};
//
//    auto start = std::chrono::high_resolution_clock::now();
//
//    std::cout << "Euler explicit method." << '\n';
//    for (const auto &h_num : h_nums)
//        euler_explicit(h_num, left, right);
//
//    std::cout << "Weight scheme." << '\n';
//    for (const auto &h_num : h_nums)
//        weight_scheme(h_num, left, right);
//
//    std::cout << "Runge-Kutta method." << '\n';
//    for (const auto &h_num : h_nums)
//        runge_kutta(h_num, left, right);
//
//    auto end = std::chrono::high_resolution_clock::now();
//
//    std::chrono::duration<double, std::milli> result = end - start;
//
//    std::cout << "Time: " << result.count() << " milli." << std::endl;
//
//    return 0;
//}

#include "src/appr_scheme.h"
#include <iostream>
#include <cmath>
#include <memory>

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
    auto exmpl = std::make_unique<euler_scheme>(10, heat_sources);

    auto results = exmpl->get_result(1.0);

    std::cout << exmpl->get_scheme_name() << std::endl;

    std::cout << "Error is " << exmpl->get_error(exact_solution) << "." << std::endl;
}
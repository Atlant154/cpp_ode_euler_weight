#include "appr_scheme.h"

#include <cmath>
#include <fstream>
#include <algorithm>

appr_scheme::appr_scheme(unsigned h_num, double (*heat_sources)(double, double)) :
        h_num_(h_num), heat_sources_(heat_sources), h_((right_bound_ - left_bound_) / h_num) {}

std::string appr_scheme::get_scheme_name() const {
    std::string name = "No name.";
    return name;
}

void appr_scheme::new_split(unsigned h_num) {
    h_ = (right_bound_ - left_bound_) / h_num;
    h_num_ = h_num;
    result.clear();
}

std::vector<std::pair<double, double>> appr_scheme::get_result(double bound_value) {
    return result;
}

double appr_scheme::get_error(double (*exact_solution)(double)) const {

    double error = 0.0;

    double appr, exact, dx;

    for (const auto &iter : result) {
        appr = fabs(iter.second);
        exact = fabs(exact_solution(iter.first));
        dx = fabs(appr - exact);
        error = (dx > error) ? dx : error;
    }
    return error;
}

void appr_scheme::write_to_file() const {

    std::fstream result_file;

    std::string filename;

    filename = "./" + get_scheme_name();

    filename += "Splits:" + std::to_string(h_num_) + "..txt";

    std::replace(filename.begin(), filename.end(), ' ', '_');

    result_file.open(filename, std::ios::out | std::ios::trunc);

    for (const auto &item : result)
        result_file << item.first << '\t' << item.second << '\n';

    result_file.close();
}

void appr_scheme::clear_result_vector() {
    result.clear();
}

euler_scheme::euler_scheme(unsigned h_num, double (*heat_sources)(double, double)) : appr_scheme(h_num, heat_sources) {}

std::vector<std::pair<double, double>> euler_scheme::get_result(double bound_value) {

    if (!result.empty())
        return result;

    result.reserve(h_num_ + 1);

    result.emplace_back(left_bound_, bound_value);

    double x, u;

    for (unsigned int iter = 1; iter <= h_num_; ++iter) {
        x = left_bound_ + iter * h_;
        u = result.back().second + h_ * heat_sources_(result.back().first, result.back().second);
        result.emplace_back(x, u);
    }
    return result;
}

std::string euler_scheme::get_scheme_name() const {
    std::string name = "Euler method.";
    return name;
}

euler_corrected_scheme::euler_corrected_scheme(unsigned h_num, double (*heat_sources)(double, double)) : appr_scheme(
        h_num, heat_sources) {};

std::vector<std::pair<double, double>> euler_corrected_scheme::get_result(double bound_value) {

    if (!result.empty())
        return result;

    result.reserve(h_num_ + 1);

    result.emplace_back(left_bound_, bound_value);

    double x, u;

    for (unsigned iter = 1; iter <= h_num_; ++iter) {
        x = left_bound_ + iter * h_;
        u = result.back().second;
        u += h_ * heat_sources_(result.back().first + 0.5 * h_, result.back().second + 0.5 * h_ * heat_sources_(
                result.back().first, result.back().second));
        result.emplace_back(x, u);
    }

    return result;
}

std::string euler_corrected_scheme::get_scheme_name() const {
    std::string name = "Euler midpoint method.";
    return name;
}

runge_kutta_scheme::runge_kutta_scheme(unsigned h_num, double (*heat_sources)(double, double)) : appr_scheme(h_num,
                                                                                                             heat_sources) {}

std::vector<std::pair<double, double>> runge_kutta_scheme::get_result(double bound_value) {

    if (!result.empty())
        return result;

    result.reserve(h_num_ + 1);

    result.emplace_back(left_bound_, bound_value);

    double k1, k2, k3, k4;

    double x, last_x, u, last_u;

    for (unsigned iter = 1; iter <= h_num_; ++iter) {
        last_x = result.back().first;
        last_u = result.back().second;
        k1 = h_ * heat_sources_(last_x, last_u);
        k2 = h_ * heat_sources_(last_x + h_ / 2.0, last_u + k1 / 2.0);
        k3 = h_ * heat_sources_(last_x + h_ / 2.0, last_u + k2 / 2.0);
        k4 = h_ * heat_sources_(last_x + h_, last_u + k3);
        x = left_bound_ + iter * h_;
        u = result.back().second + (k1 + 2 * k2 + 2 * k3 + k4) / 6.0;
        result.emplace_back(x, u);
    }

    return result;
}

std::string runge_kutta_scheme::get_scheme_name() const {
    std::string name = "Runge-Kutta method.";
    return name;
}

weight_scheme::weight_scheme(unsigned h_num, double (*heat_sources)(double, double)) : appr_scheme(h_num,
                                                                                                   heat_sources) {}

std::vector<std::pair<double, double>> weight_scheme::get_result(double bound) {

    if (!result.empty())
        return result;

    result.reserve(h_num_ + 1);

    result.emplace_back(left_bound_, bound);

    result.emplace_back(left_bound_ + h_, h_ * heat_sources_(left_bound_, bound));

    double x, u;

    double sigma = 1.5;

    for (unsigned iter = 2; iter <= h_num_; ++iter) {
        x = left_bound_ + iter * h_;
        u = result.back().second * ((2 - 2 * sigma - 4 * h_) / (2 - sigma));
        u += result[iter - 2].second * sigma / (2 - sigma);
        u += 2 * h_ * heat_sources_(result.back().first, result.back().second) / (2 - sigma);
        result.emplace_back(x, u);
    }

    return result;
}

std::string weight_scheme::get_scheme_name() const {
    std::string name = "Weight scheme.";
    return name;
}
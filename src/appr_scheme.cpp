#include "appr_scheme.h"

#include <cmath>
#include <fstream>

appr_scheme::appr_scheme(unsigned h_num, double (*heat_sources)(double)) :
      h_num_(h_num)
    , heat_sources_(heat_sources)
    , h_((right_bound_ - left_bound_) / h_num)
{}

std::string appr_scheme::get_scheme_name() const {
    std::string name = "No name.";
    return name;
}

double appr_scheme::get_error(double (*exact_solution)(double)) const {
    double error = 0.0;

    double appr, exact;

    for(unsigned long iter = 0; iter < result.size(); ++iter)
    {
        appr = result[iter].second;
        exact = exact_solution(left_bound_ + static_cast<double>(iter) * h_);
        error = pow(appr - exact, 2);
    }
    return sqrt(error * h_);
}

void appr_scheme::write_to_file() const {

    std::fstream result_file;

    std::string filename;

    filename = "./" + get_scheme_name();

    filename += "Splits: " + std::to_string(h_num_) + ".";

    result_file.open(filename, std::ios::out | std::ios::trunc);

    for (const auto &item : result)
        result_file << item.first << '\t' << item.second << '\n';

    result_file.close();
}

void appr_scheme::clear_result_vector() {
    result.clear();
}

std::vector<std::pair<double, double>> euler_scheme::get_result(double bound_value) {

    if(!result.empty())
        return result;

    result.reserve(h_num_ + 1);

    result.emplace_back(std::make_pair(left_bound_, bound_value));

    double x, u;

    for(unsigned int iter = 1; iter <= h_num_; ++iter)
    {
        x = left_bound_ + iter * h_;
        u = result.back().second + h_ * heat_sources_(result.back().first);
        result.emplace_back(x, u);
    }
    return result;
}

std::string euler_scheme::get_scheme_name() const{
    std::string name = "Euler method.";
    return name;
}

std::vector<std::pair<double, double>> runge_kutta_schene::get_result(double bound_value) {

    if(!result.empty())
        return result;

    result.reserve(h_num_ + 1);

    result.emplace_back(left_bound_, bound_value);

    double k1, k2, k3, k4;

    double x, last_x, u;

    for(unsigned iter = 1; iter <= h_num_; ++iter)
    {
        last_x = result.back().first;
        k1 = h_ * last_x;
        k2 = k3 = h_ * (last_x + h_ / 2.0);
        k4 = h_ * (last_x + h_);
        x  = left_bound_ + iter * h_;
        u  = result.back().second + (k1 + 2 * k2 + 2 * k3 + k4) / 6.0;
        result.emplace_back(x, u);
    }

    return result;
}

std::string runge_kutta_schene::get_scheme_name() const {
    std::string name = "Runge-Kutta method.";
    return name;
}

std::vector<std::pair<double, double>> weight_scheme::get_result(double bound_1, double bound_2, double sigma) {

    if(!result.empty())
        return result;

    result.reserve(h_num_ + 1);

    result.emplace_back(left_bound_, bound_1);

    result.emplace_back(left_bound_ + h_, bound_2);

    double x, u;

    for(unsigned iter = 2; iter <= h_num_; ++iter)
    {
        x  = left_bound_ + iter * h_;
        u  = result.back().second * ((2 - 2 * sigma - 4 * h_) / (2 - sigma));
        u += result[iter - 2].second * sigma / (2 - sigma);
        u += 2 * h_ * heat_sources_(result.back().first) / (2 - sigma);
        result.emplace_back(x, u);
    }

    return result;
}

std::string weight_scheme::get_scheme_name() const {
    std::string name = "Weight scheme.";
    return name;
}
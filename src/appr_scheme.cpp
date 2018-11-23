#include "appr_scheme.h"

#include <cmath>

appr_scheme::appr_scheme(unsigned h_num, double (*heat_sources)(double)) :
      h_num_(h_num)
    , heat_sources_(heat_sources)
    , h_((right_bound_ - left_bound_) / h_num)
{}

std::string appr_scheme::get_scheme_name() const {
    std::string name = "No name.";
    return name;
}

std::vector<std::pair<double, double>> appr_scheme::get_result(std::vector<double> bounds) {
    return result;
}


double appr_scheme::get_error(double (*exact_solution)(double)) const {
    double error = 0.0;

    double appr, exact;

    for(unsigned long iter = 0; iter < result.size(); ++iter)
    {
        appr = result[iter].second;
        exact = exact_solution(left_bound_ + iter * static_cast<double>(h_));
        error += pow(appr - exact, 2);
    }
    return sqrt(error * h_);
}

std::vector<std::pair<double, double>> euler_scheme::get_result(std::vector<double> bounds) {

    if(!result.empty())
        return result;

    result.reserve(h_num_ + 1);

    double x, u;

    result.emplace_back(std::make_pair(left_bound_, bounds.front()));

    for(unsigned int iter = 1; iter <= h_num_; ++iter)
    {
        x = left_bound_ + iter * h_;
        u = result.back().second + h_ * heat_sources_(result.back().first);
        result.emplace_back(std::make_pair(x, u));
    }
    return result;
}

std::string euler_scheme::get_scheme_name() const{
    std::string name = "Euler method.";
    return name;
}
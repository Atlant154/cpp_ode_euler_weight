#include "appr_scheme.h"

#include <cmath>

euler_scheme::euler_scheme(unsigned h_num, double (*heat_sources)(double)) :
      h_num_(h_num)
    , heat_sources_(heat_sources)
    , h_((right_bound_ - left_bound_) / h_num)
{};

std::string appr_scheme::get_scheme_name() const {
    return scheme_name;
}

double appr_scheme::get_error(double (*exact_solution)(double)) const {
    double error = 0.0;

    double appr, exact;

    for(auto iter = 0; iter < result.size(); ++iter)
    {
        appr = result[iter].second;
        exact = exact_solution(left_bound_ + iter * h_);
        error += pow(appr - exact, 2);
    }
    return sqrt(error * h_);
}

std::vector<std::pair<double, double>> euler_scheme::get_result(double bound_value) {

    result.reserve(h_num_ + 1);

    result.emplace_back(std::make_pair(left_bound_, bound_value));

    double x, u;

    for(auto iter = 0; iter <= h_num_; ++iter)
    {
        x = left_bound_ + iter * h_;
        u = result.back().second + h_ * heat_sources_(result.back().first);
        result.emplace_back(std::make_pair(x, u));
    }
}
#include <iostream>
#include <utility>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

auto exact_solution(double x) {
    return x * cos(x);
}

auto rh_function(double x) {
    return 2 * x * cos(x) + cos(x) - x * sin(x);
}

auto write_file(std::vector<std::pair<double, double>> &result, const std::string &filename) {
    std::fstream result_file;
    result_file.open(filename, std::ios::out | std::ios::trunc);

    for (const auto &item : result)
        result_file << item.first << '\t' << item.second << "\n";

    result_file.close();
}

auto get_error(const std::vector<std::pair<double, double>> &appr_result, double h) {
    double error = 0.0;
    double abs_exact, abs_apr, abs_diff;

    for (unsigned iter = 0; iter < appr_result.size(); ++iter) {
        abs_exact = fabs(exact_solution(iter * h));
        abs_apr = fabs(appr_result.at(iter).second);
        abs_diff = fabs(abs_exact - abs_apr);
        error = abs_diff > error ? abs_diff : error;
    }

    return error;
}

auto euler_explicit(unsigned const h_num, double const h, double const left) {
    std::vector<std::pair<double, double >> result;
    result.reserve(h_num);

    /*
     * Service variables:
     * x - 0x coordinates, u - 0y coordinates(method approximation values).
    */
    double x;
    double u;

    result.emplace_back(std::make_pair(0.0, 0.0));

    for (unsigned iter = 0; iter < h_num; ++iter) {
        x = left + iter * h;
        u = result.back().second + h * (rh_function(result.back().first) - 2 * result.back().second);
        result.emplace_back(std::make_pair(x, u));
    }

    std::string filename = "euler_result_Splits:" + std::to_string(h_num) + ".txt";

    write_file(result, filename);

    auto error = get_error(result, h);

    std::cout << "H nodes number: " << h_num << ". Max error is " << error << "." << std::endl;
}

int main() {

    const double left = 0.0;
    const double right = 1.0;

    double h;

    std::vector<unsigned> h_nums = {16, 128, 512, 1024};

    std::cout << "Euler explicit method." << '\n';
    for (const auto &h_num : h_nums) {
        h = (right - left) / h_num;
        euler_explicit(h_num, h, left);
    }
}
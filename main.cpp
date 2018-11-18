#include <iostream>
#include <utility>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

double exact_solution(double x) {
    return x * cos(x);
}

double rh_function(double x) {
    return 2 * x * cos(x) + cos(x) - x * sin(x);
}

void write_file(const std::vector<std::pair<double, double>> &result, const std::string &filename) {
    std::fstream result_file;
    result_file.open(filename, std::ios::out | std::ios::trunc);

    for (const auto &item : result)
        result_file << item.first << '\t' << item.second << "\n";

    result_file.close();
}

double get_error(const std::vector<std::pair<double, double>> &appr_result, double const h, double const left) {
    double error = 0.0;
    double abs_exact, abs_apr, abs_diff;

    for (unsigned iter = 0; iter < appr_result.size(); ++iter) {
        abs_exact = fabs(exact_solution(left + iter * h));
        abs_apr = fabs(appr_result.at(iter).second);
        abs_diff = fabs(abs_exact - abs_apr);
        error = abs_diff > error ? abs_diff : error;
    }

    return error;
}

void euler_explicit(unsigned const h_num, double const left, double const right) {

    double h = (right - left) / h_num;

    std::vector<std::pair<double, double >> result;
    result.reserve(h_num + 1);

    /*
     * Service variables:
     * x - 0x coordinates, u - 0y coordinates(method approximation values).
    */
    double x;
    double u;

    result.emplace_back(std::make_pair(0.0, 0.0));

    for (unsigned iter = 1; iter <= h_num; ++iter) {
        x = left + iter * h;
        u = result.back().second + h * (rh_function(result.back().first) - 2 * result.back().second);
        result.emplace_back(std::make_pair(x, u));
    }

    std::string filename = "euler_result_Splits:" + std::to_string(h_num) + ".txt";

    write_file(result, filename);

    auto error = get_error(result, h, left);

    std::cout << "H nodes number: " << h_num << ". Max error is " << error << "." << std::endl;
}

void weight_scheme(unsigned const h_num, double const left, double const right) {

    double h = (right - left) / h_num;

    std::vector<std::pair<double, double>> result;
    result.reserve(h_num + 1);

    double x, u;

    result.emplace_back(std::make_pair(left, 0.0));
    result.emplace_back(std::make_pair(h, h * rh_function(left)));

    double sigma = 1.0;

    for (unsigned iter = 2; iter <= h_num; ++iter) {
        x = left + iter * h;
        u = result.back().second * ((2 - 2 * sigma - 4 * h) / (2 - sigma));
        u += result.at(iter - 2).second * sigma / (2 - sigma);
        u += 2 * h * rh_function(result.at(iter - 1).first) / (2 - sigma);
        result.emplace_back(std::make_pair(x, u));
    }

    std::string filename = "weight_scheme_Splits:" + std::to_string(h_num) + ".txt";

    write_file(result, filename);

    auto error = get_error(result, h, left);

    std::cout << "H nodes number: " << h_num << ". Max error is " << error << "." << std::endl;
}

int main() {

    const double left = 0.0;
    const double right = 1.0;

    std::vector<unsigned> h_nums = {16, 128, 512, 1024};

    std::cout << "Euler explicit method." << '\n';
    for (const auto &h_num : h_nums) {
        euler_explicit(h_num, left, right);
    }

    std::cout << "Weight scheme." << '\n';
    for (const auto &h_num : h_nums) {
        weight_scheme(h_num, left, right);
    }

    return 0;
}